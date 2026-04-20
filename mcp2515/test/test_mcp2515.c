
#include "unity.h"
#include "mcp2515.h"
#include "mock_spi_wrapper.h"
static st_mcp2515_spi_t st_mcp2515_spi;
static pst_mcp2515_t pst_mcp2515;
void setUp(void)
{
	st_mcp2515_spi.cs_pin = 0xCC;
	st_mcp2515_spi.send_byte = spi_send_byte;
	st_mcp2515_spi.receive_byte = spi_receive_byte;
	st_mcp2515_spi.start_com = spi_start_com;
	st_mcp2515_spi.end_com = spi_start_com;
	pst_mcp2515 = mcp2515_Init(&st_mcp2515_spi);
}

void tearDown(void)
{

}

void test_shouldReturnNonNull_afterInitedWithSpiConfig(void)
{
	pst_mcp2515_t ret_pointer = NULL;
	ret_pointer = mcp2515_Init(&st_mcp2515_spi);
	TEST_ASSERT_FALSE(NULL == ret_pointer);
}

void test_shouldBeInited_afterInited()
{
	bool is_inited = false;
	pst_mcp2515_t tst_pst_mcp2515 = mcp2515_Init(&st_mcp2515_spi);
	is_inited = mcp2515_isInited(tst_pst_mcp2515);
	TEST_ASSERT_TRUE(is_inited == true);
}
