#include "flash.h"

/**
  * @brief  Gets the sector of a given address
  * @param  None
  * @retval The sector of a given address
  */
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_Sector_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_Sector_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_Sector_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_Sector_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_Sector_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_Sector_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_Sector_10;  
  }
  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_Sector_11;  
  }

  return sector;
}

extern void Flash_Write(void)
{
    uint32_t StartSector = 0, EndSector = 0,i = 0;
  	uint32_t Address = 0;


    FLASH_Unlock();

    
  /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  /* Clear pending flags (if any) */  
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 

    /* Get the number of the start and end sectors */
    StartSector = GetSector(FLASH_USER_START_ADDR);
    EndSector = GetSector(FLASH_USER_END_ADDR);
    EndSector = StartSector + 8;
	 
    for (i = StartSector; i < EndSector; i += 8)
    {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
        if (FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE)
        { 
						
            /* Error occurred while sector erase. 
             * User can add here some code to deal with this error  */
            while (1)
            {
							
            }
        }
    }
    Address = FLASH_USER_START_ADDR;
    FLASH_ProgramByte(Address,gl_car.num);
    FLASH_ProgramByte(Address+1,gl_pos);
    /* Lock the Flash to disable the flash control register access (recommended
     * to protect the FLASH memory against possible unwanted operation) *********/
    FLASH_Lock();
}

extern void Flash_Read(void)
{
    uint32_t Address = 0;
    Address = FLASH_USER_START_ADDR;
    gl_car.num = *(__IO uint32_t*)Address;
    Address = Address + 1;
    gl_pos = *(__IO uint32_t*)Address;
}

