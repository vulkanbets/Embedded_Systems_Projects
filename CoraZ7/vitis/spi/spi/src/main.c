
#include "xparameters.h"	/* XPAR parameters */
#include "xspi.h"		/* SPI device driver */
#include "xspi_l.h"
#include "xil_printf.h"

/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define SPI_DEVICE_ID		XPAR_SPI_0_DEVICE_ID

/*
 *  This is the # of bytes to be transmitted/received in this example.
 */
#define BYTE_COUNT		1

/************************** Variable Definitions *****************************/

/*
 * The instances to support the device drivers are global such that the
 * are initialized to zero each time the program runs.
 */
static XSpi  SpiInstance;	 /* The instance of the SPI device */

/*
 * The following variables are used to read and write to the Spi device, they
 * are global to avoid having large buffers on the stack.
 */
u8 SendBuffer[BYTE_COUNT];


int main(void)
{
	int Status;

	XSpi_Config *ConfigPtr;	/* Pointer to Configuration data */

	/*
	 * Initialize the SPI driver so that it is  ready to use.
	 */
	ConfigPtr = XSpi_LookupConfig(SPI_DEVICE_ID);
	if (ConfigPtr == NULL) {
		return XST_DEVICE_NOT_FOUND;
	}

	Status = XSpi_CfgInitialize(&SpiInstance, ConfigPtr, ConfigPtr->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XSpi_SelfTest(&SpiInstance);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Only continue if set to Standard mode
	 */
	if ( SpiInstance.SpiMode != XSP_STANDARD_MODE ) {
		return XST_SUCCESS;
	}

	/*
	 * Set the Spi device in master mode.
	 */
	Status = XSpi_SetOptions( &SpiInstance, XSP_MASTER_OPTION );
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Start the SPI driver so that the device is enabled.
	 */
	XSpi_Start(&SpiInstance);

	/*
	 * Disable Global interrupt to use polled mode operation
	 */
	XSpi_IntrGlobalDisable(&SpiInstance);

	/*
	 * Set the slave select bit.
	 */
	XSpi_SetSlaveSelect(&SpiInstance, 0x01);

	/*
	 * Send byte 8'b01010011 through MOSI Line
	 */
	SendBuffer[0] = 0x53;


	while (1)
	{
		xil_printf("Data Width  => %d\r\n", SpiInstance.DataWidth);
		xil_printf("SPI Mode  => %d\r\n", SpiInstance.SpiMode);
		xil_printf("FIFO Depth  => %d\r\n", SpiInstance.FifosDepth);
		xil_printf("Number of Slave Selects for the Device  => %d\r\n", SpiInstance.NumSlaveBits);
		xil_printf("Bytes Transferred  => %d\r\n", SpiInstance.Stats.BytesTransferred);

		/*
		 * Transmit the data.
		 */
		XSpi_Transfer(&SpiInstance, SendBuffer, NULL, BYTE_COUNT);


		xil_printf("\r\n");
		xil_printf("\r\n");
	}

	return 0;
}

