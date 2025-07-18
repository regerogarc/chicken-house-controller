/*****************************************************************************
* | File        :   OLED_0in49.c
* | Author      :
* | Function    :   0.49inch OLED  Drive function
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-03-16
* | Info        :
* -----------------------------------------------------------------------------
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
******************************************************************************/
#include "OLED_0in49.h"
#include "stdio.h"

/*******************************************************************************
function:
            Hardware reset
*******************************************************************************/
static void I2C_Write_Byte(uint8_t reg,uint8_t Value)
{
    DEV_I2C_Write(OLED_0in49_ADDR, reg, Value);
}

static void OLED_Reset(void)
{
    OLED_RST_1;
    DEV_Delay_ms(100);
    OLED_RST_0;
    DEV_Delay_ms(100);
    OLED_RST_1;
    DEV_Delay_ms(100);
}

/*******************************************************************************
function:
            Write register address and data
*******************************************************************************/
static void OLED_WriteReg(uint8_t Reg)
{
#if USE_SPI
    OLED_DC_0;
    OLED_CS_0;
    DEV_SPI_WriteByte(Reg);
    OLED_CS_1;
#elif USE_IIC
    I2C_Write_Byte(IIC_CMD,Reg);
#endif
}

static void OLED_WriteData(uint8_t Data)
{
#if USE_SPI
    OLED_DC_1;
    OLED_CS_0;
    DEV_SPI_WriteByte(Data);
    OLED_CS_1;
#elif USE_IIC
    I2C_Write_Byte(IIC_RAM,Data);
#endif
}

/*******************************************************************************
function:
            Common register initialization
*******************************************************************************/
static void OLED_InitReg(void)
{
    // 
    // Initialize dispaly
    //

    // OLED_WriteReg(0xAE); /*display off*/

    // OLED_WriteReg(0x00); /*set lower column address*/
    // OLED_WriteReg(0x12); /*set higher column address*/

    // OLED_WriteReg(0x00); /*set display start line*/

    // OLED_WriteReg(0xB0); /*set page address*/


    // OLED_WriteReg(0x81); /*contract control*/
    // OLED_WriteReg(0x4f); /*128*/

    // OLED_WriteReg(0xA0); /*set segment remap*/

    // OLED_WriteReg(0xA6); /*normal / reverse*/

    // OLED_WriteReg(0xA8); /*multiplex ratio*/
    // OLED_WriteReg(0x1F); /*duty = 1/32*/


    // OLED_WriteReg(0xC8); /*Com scan direction*/

    // OLED_WriteReg(0xD3); /*set display offset*/
    // OLED_WriteReg(0x00);

    // OLED_WriteReg(0x20);
    // OLED_WriteReg(0x01); /*set Vertical Addressing Mode*/

    // OLED_WriteReg(0xD5); /*set osc division*/
    // OLED_WriteReg(0x80);

    // OLED_WriteReg(0xD9); /*set pre-charge period*/
    // OLED_WriteReg(0xf1);

    // OLED_WriteReg(0xDA); /*set COM pins*/
    // OLED_WriteReg(0x12);

    // OLED_WriteReg(0xdb); /*set vcomh*/
    // OLED_WriteReg(0x40);

    // OLED_WriteReg(0x8d); /*set charge pump enable*/
    // OLED_WriteReg(0x14);

    // OLED_WriteReg(0xAF); /*display ON*/

    OLED_WriteReg(0xAE);//--turn off oled panel

    OLED_WriteReg(0x00);//---set low column address
    OLED_WriteReg(0x10);//---set high column address
    
    OLED_WriteReg(0x20);
    OLED_WriteReg(0x00);
        
    OLED_WriteReg(0xFF);
    
    OLED_WriteReg(0xA6);
    
    OLED_WriteReg(0xA8); 
    OLED_WriteReg(0x3F);
    
    OLED_WriteReg(0xD3);
    OLED_WriteReg(0x00);
    
    OLED_WriteReg(0xD5);
    OLED_WriteReg(0x80);
    
    OLED_WriteReg(0xD9);
    OLED_WriteReg(0x22);

    OLED_WriteReg(0xDA);
    OLED_WriteReg(0x12);
    
    OLED_WriteReg(0xDB);
    OLED_WriteReg(0x40);
    
}

/********************************************************************************
function:
            initialization
********************************************************************************/
void OLED_0in49_Init()
{
// Hardware reset
#if USE_SPI
    OLED_Reset();
#endif
    // Set the initialization register
    OLED_InitReg();

    sleep_ms(200);
    OLED_WriteReg(0xAF);
}

/********************************************************************************
function:
            Clear screen
********************************************************************************/
void OLED_0in49_Clear(void)
{
    // UWORD i;
    // OLED_WriteReg(0x22); // 设置页面地址
    // OLED_WriteReg(0x00);
    // OLED_WriteReg(0x03);
    // OLED_WriteReg(0x21); // 设置列地址
    // OLED_WriteReg(0x20);
    // OLED_WriteReg(0x5f);

    // for (i = 0; i < 1024; i++)
    // {
    //     OLED_WriteData(0XFF);
    // }

        // UWORD Width, Height;
    UWORD i, j;
    // Width = (OLED_1IN3_WIDTH % 8 == 0)? (OLED_1IN3_WIDTH / 8 ): (OLED_1IN3_WIDTH / 8 + 1);
    // Height = OLED_1IN3_HEIGHT; 
    for (i=0; i<8; i++) {
        /* set page address */
        OLED_WriteReg(0xB0 + i);
        /* set low column address */
        OLED_WriteReg(0x00);
        /* set high column address */
        OLED_WriteReg(0x10);
        for(j=0; j<128; j++) {
            /* write data */
            OLED_WriteData(0x00);  
        }

    }
}

/********************************************************************************
function:
            reverse a byte data
********************************************************************************/
static UBYTE reverse(UBYTE temp)
{
    temp = ((temp & 0x55) << 1) | ((temp & 0xaa) >> 1);
    temp = ((temp & 0x33) << 2) | ((temp & 0xcc) >> 2);
    temp = ((temp & 0x0f) << 4) | ((temp & 0xf0) >> 4);
    return temp;
}

/********************************************************************************
function:
    Update all memory to OLED
********************************************************************************/
void OLED_0in49_Display(const UBYTE *Image)
{
    // UBYTE temp;
    // UWORD i;
    // OLED_WriteReg(0x22);
    // OLED_WriteReg(0x00);
    // OLED_WriteReg(0x03);
    // OLED_WriteReg(0x21);
    // OLED_WriteReg(0x20);
    // OLED_WriteReg(0x5f);
    // for (i = 0; i < 256; i++)
    // {
    //     temp = Image[i];
    //     temp = reverse(temp); // reverse the buffer
    //     OLED_WriteData(temp);
    // }

    UWORD page, column, temp;

    for (page=0; page<8; page++) {
        /* set page address */
        OLED_WriteReg(0xB0 + page);
        /* set low column address */
        OLED_WriteReg(0x00);
        /* set high column address */
        OLED_WriteReg(0x10);

        /* write data */
        for(column=0; column<128; column++) {
            temp = Image[(7-page) + column*8];
            OLED_WriteData(temp);
        }       
    }
}