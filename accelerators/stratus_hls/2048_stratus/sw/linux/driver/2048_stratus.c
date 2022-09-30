// Copyright (c) 2011-2021 Columbia University, System Level Design Group
// SPDX-License-Identifier: Apache-2.0
#include <linux/of_device.h>
#include <linux/mm.h>

#include <asm/io.h>

#include <esp_accelerator.h>
#include <esp.h>

#include "2048_stratus.h"

#define DRV_NAME	"2048_stratus"

/* <<--regs-->> */
#define 2048_ROW_REG 0x44
#define 2048_BOARD_REG 0x40

struct 2048_stratus_device {
	struct esp_device esp;
};

static struct esp_driver 2048_driver;

static struct of_device_id 2048_device_ids[] = {
	{
		.name = "SLD_2048_STRATUS",
	},
	{
		.name = "eb_36a",
	},
	{
		.compatible = "sld,2048_stratus",
	},
	{ },
};

static int 2048_devs;

static inline struct 2048_stratus_device *to_2048(struct esp_device *esp)
{
	return container_of(esp, struct 2048_stratus_device, esp);
}

static void 2048_prep_xfer(struct esp_device *esp, void *arg)
{
	struct 2048_stratus_access *a = arg;

	/* <<--regs-config-->> */
	iowrite32be(a->row, esp->iomem + 2048_ROW_REG);
	iowrite32be(a->board, esp->iomem + 2048_BOARD_REG);
	iowrite32be(a->src_offset, esp->iomem + SRC_OFFSET_REG);
	iowrite32be(a->dst_offset, esp->iomem + DST_OFFSET_REG);

}

static bool 2048_xfer_input_ok(struct esp_device *esp, void *arg)
{
	/* struct 2048_stratus_device *2048 = to_2048(esp); */
	/* struct 2048_stratus_access *a = arg; */

	return true;
}

static int 2048_probe(struct platform_device *pdev)
{
	struct 2048_stratus_device *2048;
	struct esp_device *esp;
	int rc;

	2048 = kzalloc(sizeof(*2048), GFP_KERNEL);
	if (2048 == NULL)
		return -ENOMEM;
	esp = &2048->esp;
	esp->module = THIS_MODULE;
	esp->number = 2048_devs;
	esp->driver = &2048_driver;
	rc = esp_device_register(esp, pdev);
	if (rc)
		goto err;

	2048_devs++;
	return 0;
 err:
	kfree(2048);
	return rc;
}

static int __exit 2048_remove(struct platform_device *pdev)
{
	struct esp_device *esp = platform_get_drvdata(pdev);
	struct 2048_stratus_device *2048 = to_2048(esp);

	esp_device_unregister(esp);
	kfree(2048);
	return 0;
}

static struct esp_driver 2048_driver = {
	.plat = {
		.probe		= 2048_probe,
		.remove		= 2048_remove,
		.driver		= {
			.name = DRV_NAME,
			.owner = THIS_MODULE,
			.of_match_table = 2048_device_ids,
		},
	},
	.xfer_input_ok	= 2048_xfer_input_ok,
	.prep_xfer	= 2048_prep_xfer,
	.ioctl_cm	= 2048_STRATUS_IOC_ACCESS,
	.arg_size	= sizeof(struct 2048_stratus_access),
};

static int __init 2048_init(void)
{
	return esp_driver_register(&2048_driver);
}

static void __exit 2048_exit(void)
{
	esp_driver_unregister(&2048_driver);
}

module_init(2048_init)
module_exit(2048_exit)

MODULE_DEVICE_TABLE(of, 2048_device_ids);

MODULE_AUTHOR("Emilio G. Cota <cota@braap.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("2048_stratus driver");
