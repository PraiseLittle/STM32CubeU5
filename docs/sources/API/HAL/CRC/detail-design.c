/*! \fn hal_status_t HAL_CRC_DeInit(hal_crc_handle_t *hcrc)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_DeInit() function:
  * 
    @startuml
    start
    :HAL_CRC_DeInit;
    :ASSERT_DBG_PARAM( CRC handle is not null );
    :ASSERT_DBG_STATE( **CRC global state** is IDLE );   
    :Reset the CRC global configuration to default;  
    :Reset the CRC independent data register to default;      
    :Reset the HAL CRC state;
    #palegreen: return HAL_OK;    
    stop
    @enduml
*/  


/*! \fn hal_status_t HAL_CRC_Init(hal_crc_handle_t *hcrc, hal_crc_t instance)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_Init() function:
  *
    @startuml
      start
      :HAL_CRC_Init;
        :ASSERT_DBG_PARAM( CRC handle is not null );
      if (defined USE_HAL_CHECK_PARAM) then (=Yes)
         if(CRC handle is null) then (= No)
         else (=Yes)
            #red:return HAL_INVALID_PARAM;
            stop
         endif
      else (=No)
      endif
      :Set the CRC instance;
      if (USE_HAL_CRC_CLK_ENABLE_MODEL == HAL_CLK_ENABLE_CRC_ONLY) then (=Yes)
        :Enable the CRC clock;
      else (=No)    
      endif        
      :Initialize the HAL CRC state to IDLE;
      #palegreen: return HAL_OK;
      stop
    @enduml
*/   
  
/*! \fn   hal_status_t HAL_CRC_SetConfig(hal_crc_handle_t *hcrc, const hal_crc_config_t *p_config)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_SetConfig() function:
  *   
    @startuml
      start
      :HAL_CRC_SetConfig;
        :ASSERT_DBG_PARAM( **CRC handle** is not null );
        :ASSERT_DBG_PARAM( **CRC configuration structure pointer** is not null );      
        :ASSERT_DBG_STATE( **CRC global state** is IDLE );  
      if (defined USE_HAL_CHECK_PARAM) then (=Yes)
         if(**CRC configuration structure pointer** is null or **The generating polynomial** is invalid) then (=No)
         else (=Yes)
            #red:return HAL_INVALID_PARAM;
            stop
         endif
      else (=No)
      endif   
      :Configure the CRC peripheral(Polynomial coefficient & size, CRC init value, Input & output reversibility modes);
      #palegreen: return HAL_OK;
      stop
    @enduml
*/  

/*! \fn   void HAL_CRC_GetConfig(const hal_crc_handle_t *hcrc, hal_crc_config_t *p_config)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_GetConfig() function:
  *   
    @startuml
    start
    :HAL_CRC_GetConfig;
    :ASSERT_DBG_PARAM( **CRC handle** is not null );
    :ASSERT_DBG_PARAM( **CRC configuration structure pointer** is not null ); 
    :ASSERT_DBG_STATE( **CRC global state** is IDLE );  
    #palegreen:Retrieve the configuration structure(Polynomial coefficient & size, CRC init value, Input & output reversibility modes);
    stop
    @enduml
*/

/*! \fn   void HAL_CRC_ResetConfig(hal_crc_handle_t *hcrc)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_ResetConfig() function:
  *   
    @startuml
    start
    :HAL_CRC_ResetConfig;
    :ASSERT_DBG_PARAM( **CRC handle** is not null ); 
    :ASSERT_DBG_STATE( **CRC global state** is IDLE );   
    #palegreen:Set the default CRC configuration;
    stop
    @enduml
*/

/*! \fn   hal_status_t HAL_CRC_SetConfigPolynomial(hal_crc_handle_t *hcrc, uint32_t poly_coefficient,
                                                   hal_crc_polynomial_size_t poly_size,
                                                   uint32_t crc_init_value)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_SetConfigPolynomial() function:
  *
    @startuml
    start
    :HAL_CRC_SetConfigPolynomial;
    :ASSERT_DBG_PARAM( **CRC handle** is not null ); 
    :ASSERT_DBG_STATE( **CRC global state** is IDLE );  
      if (defined USE_HAL_CHECK_PARAM) then (=Yes)
        if(**The generating polynomial** is invalid) then (=No)
        else (=Yes)
          #red:return HAL_INVALID_PARAM;
          stop
        endif
    else (=No)
    endif 
    :Configure the CRC polynomial user coefficient and size and the CRC init value;
    #palegreen: return HAL_OK;
    stop
 @enduml   
*/

/*! \fn   void HAL_CRC_SetInputReverseMode(hal_crc_handle_t *hcrc, hal_crc_input_data_reverse_mode_t input_reverse_mode)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_SetInputReverseMode() function:
  *
    @startuml
    start
    :HAL_CRC_SetInputReverseMode;
    :ASSERT_DBG_PARAM( **CRC handle** is not null ); 
    :ASSERT_DBG_STATE( **CRC global state** is IDLE );   
    #palegreen:Configure the input reversibility mode;
    stop
    @enduml   
*/

/*! \fn   hal_crc_input_data_reverse_mode_t HAL_CRC_GetInputReverseMode(const hal_crc_handle_t *hcrc)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_GetInputReverseMode() function:
  *
    @startuml
    start
    :HAL_CRC_GetInputReverseMode;
    :ASSERT_DBG_PARAM( **CRC handle** is not null ); 
    :ASSERT_DBG_STATE( **CRC global state** is IDLE );  
    #palegreen:Retrieve the configured input reversibility mode;
    stop
  @enduml  
*/

/*! \fn   void HAL_CRC_SetOutputReverseMode(hal_crc_handle_t *hcrc, hal_crc_output_data_reverse_mode_t output_reverse_mode)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_SetOutputReverseMode() function:
  *
    @startuml
    start
    :HAL_CRC_SetOutputReverseMode;
    :ASSERT_DBG_PARAM( **CRC handle** is not null ); 
    :ASSERT_DBG_STATE( **CRC global state** is IDLE );  
    #palegreen:Configure the output reversibility mode;
    stop
    @enduml   
*/

/*! \fn   hal_crc_output_data_reverse_mode_t HAL_CRC_GetOutputReverseMode(const hal_crc_handle_t *hcrc)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_GetOutputReverseMode() function:
  *
    @startuml
    start
    :HAL_CRC_GetOutputReverseMode;
    :ASSERT_DBG_PARAM( **CRC handle** is not null ); 
    :ASSERT_DBG_STATE( **CRC global state** is IDLE );  
    #palegreen:Retrieve the configured output reversibility mode;
    stop
  @enduml  
*/

/*! \fn   void HAL_CRC_SetIndependentData(hal_crc_handle_t *hcrc, uint32_t independant_data)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_SetIndependentData() function:
  *
    @startuml
    start
    :HAL_CRC_SetIndependentData;
    :ASSERT_DBG_PARAM( **CRC handle** is not null ); 
    :ASSERT_DBG_STATE( **CRC global state** is IDLE );  
    #palegreen:Configure temporarily an independent data value;
    stop
    @enduml   
*/

/*! \fn   uint32_t HAL_CRC_GetIndependentData(const hal_crc_handle_t *hcrc)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_GetIndependentData() function:
  *
    @startuml
    start
    :HAL_CRC_GetIndependentData;
    :ASSERT_DBG_PARAM( **CRC handle** is not null ); 
    :ASSERT_DBG_STATE( **CRC global state** is IDLE );    
    #palegreen:Retrieve the independent temporarily stored data;
    stop
  @enduml  
*/

/*! \fn   hal_status_t HAL_CRC_Accumulate(hal_crc_handle_t *hcrc, const void *p_data, uint32_t size_byte, uint32_t *crc_result)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_Accumulate() function:
  *   
    @startuml
      start
      :HAL_CRC_Accumulate;
         :ASSERT_DBG_PARAM( **CRC handle** is not null ); 
         :ASSERT_DBG_PARAM( **User data pointer** is not null );    
         :ASSERT_DBG_PARAM( **User data buffer** is not empty );   
        :ASSERT_DBG_STATE( **CRC global state** is IDLE );  
      if (defined USE_HAL_CHECK_PARAM) then (=Yes)
         if( **User data pointer** is null or **User data buffer** is empty ) then (=No)
         else (=Yes)
            #red:return HAL_INVALID_PARAM;
            stop
         endif
      else (=No)
      endif  
      if (defined USE_HAL_CHECK_PROCESS_STATE) then (=Yes)
        if (**CRC global state** is not IDLE) then (=Yes)   
            #Orange:return HAL_BUSY;
            stop
        else (=No)
        endif
      else (=No)
      endif
      :CRC global State = ACTIVE;
    
      :Calculate CRC;
      :CRC global State = IDLE;
      #palegreen: return HAL_OK;
      stop
    @enduml
*/

/*! \fn   hal_status_t HAL_CRC_Calculate(hal_crc_handle_t *hcrc, const void *p_data, uint32_t size_byte, uint32_t *crc_result)
  * @par Detailed design
  * The following graph shows the processing of the HAL_CRC_Calculate() function:
  *   
    @startuml
      start
      :HAL_CRC_Calculate;
         :ASSERT_DBG_PARAM( **CRC handle** is not null ); 
         :ASSERT_DBG_PARAM( **User data pointer** is not null );    
         :ASSERT_DBG_PARAM( **User data buffer** is not empty );   
        :ASSERT_DBG_STATE( **CRC global state** is IDLE );  
      if (defined USE_HAL_CHECK_PARAM) then (=Yes)
         if( **User data pointer** is null or **User data buffer** is empty ) then (=No)
         else (=Yes)
            #red:return HAL_INVALID_PARAM;
            stop
         endif
      else (=No)
      endif  
      if (defined USE_HAL_CHECK_PROCESS_STATE) then (=Yes)
        if (**CRC global state** is not IDLE) then (=Yes)   
            #Orange:return HAL_BUSY;
            stop
        else (=No)
        endif
      else (=No)
      endif
      :CRC global State = ACTIVE;
         
      :Reset the CRC calculation unit; 
      :Calculate CRC;
      :Global State = IDLE;
      #palegreen: return HAL_OK;
      stop
    @enduml
*/

/*! \fn   hal_status_t CRC_CheckPolynomial(uint32_t poly_coefficient, hal_crc_polynomial_size_t poly_size)
  * @par Detailed design
  * The following graph shows the processing of the CRC_CheckPolynomial() function:
  *
    @startuml
    start
    :CRC_CheckPolynomial;
    if ( **The user polynomial** is even) then (=Yes)
      #red:return HAL_INVALID_PARAM;
      stop
    else (=No)
    endif
    :Determine the degree of the user polynomial;  
    if ( **The user polynomial size and degree** are coherent) then (=Yes)
    #palegreen: return HAL_OK;
    stop
    else (=No)
    #red:return HAL_INVALID_PARAM; 
    stop
 @enduml   
*/

/*! \fn   static uint32_t CRC_FeedData(hal_crc_handle_t *hcrc, const uint8_t *p_data, uint32_t size_byte)
  * @par Detailed design
  * The following graph shows the processing of the CRC_FeedData() function:
  *   
    @startuml
      start
      :CRC_FeedData;

         if (user buffer lenght >= 4 bytes ) then (=1)

               if (user buffer not aligned 16-bits) then (=1)
               :Feed DR register with one byte;
               :user buffer adresse++;
               else ()
               endif

               if (user buffer not aligned 32-bits) then (=1)
               :Feed DR register with one halfword;
               :user buffer adresse +=2;
               -> **The user buffer is now aligned 32-bits**;
               else ()
               endif

               repeat 
                  :Feed DR register with words;
                  :user buffer adresse +=4;
               repeat while ()

         endif

         if (2 bytes or more lasts) then (=1)
         :Feed DR register with one halfword;
         :user buffer adresse +=2;
         else (=0)
         endif

         if (1 or 3 bytes lasts) then (=1)
         :Feed DR register with last byte;
         else (=0)
         endif

      #palegreen: return the calculated CRC;
      stop
    @enduml
*/