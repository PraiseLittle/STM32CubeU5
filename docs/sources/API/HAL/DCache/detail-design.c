/*! \fn hal_status_t HAL_DCACHE_Init(hal_dcache_handle_t *hdcache, hal_dcache_t instance)
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_Init:
  *
  * @startuml
  * start
  *   :Check the HAL DCACHE Handle is not NULL;
  *   if (USE_HAL_CHECK_PARAM) then (=1)
  *     if(hdcache) then (!=NULL)
  *     else (=NULL)
  *       #yellow:return HAL_INVALID_PARAM;
  *       stop
  *     endif
  *   else (=0)
  *   endif
  *   :Set the DCACHE instance;
  *     if (USE_HAL_DCACHE_CLK_ENABLE_MODEL) then (=1)
  *         :Enable DCACHE Clock;
  *     else (=0)    
  *     endif    
  *   if (USE_HAL_DCACHE_REGISTER_CALLBACKS) then (=1)
  *     :Initialize the HAL DCACHE Callbacks;
  *   else (=0)
  *   endif
  *   #ccf:State = IDLE\\
  *   #palegreen: return HAL_OK;
  * stop
  * @enduml
  * @hidecallgraph
  */

 
/*! \fn void HAL_DCACHE_DeInit(hal_dcache_handle_t *hdcache)
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_DeInit:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the HAL DCACHE State is IDLE or ACTIVE or MAINTENANCE;
  *     :Reset the Monitors;
  *     :Reset the Control Register: Read Burst Type to WRAP, all command operations finished, Data Cache disabled;
  *     :Reset the Interrupt Enable Register: clear ERRIE, CMDENDIE and BSYENDIE flags; 
  *     :Reset the Flag Clear Register: clear ERR, CMDEND and BSYEND flags;
  *     #ccf:State = RESET\\
  * stop
  * @enduml
  */
  
  
/*! \fn hal_status_t HAL_DCACHE_SetReadBurstType(hal_dcache_handle_t *hdcache, hal_dcache_read_burst_t read_burst_type)
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_SetReadBurstType:
  *  
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the HAL DCACHE State is ACTIVE;
  *     if (DCACHE Enabled ?) then (Yes)
  *         #red: return HAL_ERROR;
  *         stop
  * 	else (No)
  *         :Set the Read Burst Type;
  * 	#palegreen: return HAL_OK;
  *     stop
  *     endif
  * @enduml
  */
  
  
/*! \fn hal_dcache_read_burst_t HAL_DCACHE_GetReadBurstType(const hal_dcache_handle_t *hdcache)
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_GetReadBurstType:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *   :Check the HAL DCACHE State is IDLE or ACTIVE or MAINTENANCE;
  *   :return the current Configuration;
  * stop
  * @enduml
  */
  
/*! \fn hal_status_t HAL_DCACHE_Start(hal_dcache_handle_t *hdcache, uint32_t interrupts);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_Start:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the HAL DCACHE State is IDLE;
  *     if (interrupts) then (===HAL_DCACHE\n===_IT_ERROR)
  *         :Enable the Error interrupt;
  *     else (===HAL_DCACHE_IT_NONE)
  *     endif    
  *     :Start the DCACHE;
  *     #ccf:State = ACTIVE\\
  * 	#palegreen: return HAL_OK;
  * stop
  * @enduml
  */   

/*! \fn hal_status_t HAL_DCACHE_Stop(hal_dcache_handle_t *hdcache);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_Stop:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the HAL DCACHE State is ACTIVE or MAINTENANCE;
  *     :Disable the Error interrupt;
  *     :Clear the Error flag;
  *     :Stop the DCACHE;
  *     #ccf:State = IDLE\\
  * 	#palegreen: return HAL_OK;
  * stop
  * @enduml
  */  

/*! \fn hal_status_t HAL_DCACHE_Invalidate(hal_dcache_handle_t *hdcache);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_Invalidate:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the HAL DCACHE State is ACTIVE;
  *     if (Flags BUSY or BUSYCMD) then (=1)
  *         #orange: status = HAL_BUSY;
  * 	else (=0)
  *         #ccf:State = MAINTENANCE\\
  *         :Clear flags BSYEND or CMDEND;
  *         :Set DCACHE Command;
  *         :Launch DCACHE Invalidation;
  *         if (DCACHE_WaitOnFlagUntilTimeout()) then (===HAL_ERROR)
  *             #red: status = HAL_ERROR;
  *         else (===HAL_OK)
  * 	        #palegreen: status = HAL_OK;
  *         endif
  *         #ccf:State = ACTIVE\\
  *     endif
  *     :Return the Status;
  * stop
  * @enduml
  */

/*! \fn hal_status_t HAL_DCACHE_InvalidateByAddr(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_InvalidateByAddr:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the Size and the Address;
  *     :Check the HAL DCACHE State is ACTIVE;
  *     if (Flags BUSY or BUSYCMD) then (=1)
  *         #orange: status = HAL_BUSY;
  * 	else (=0)
  *         #ccf:State = MAINTENANCE\\
  *         :DCACHE_CommandByAddr();
  *         :Launch the corresponding DCACHE Command;
  *         if (DCACHE_WaitOnFlagUntilTimeout()) then (===HAL_ERROR)
  *             #red: status = HAL_ERROR;
  *         else (===HAL_OK)
  * 	        #palegreen: status = HAL_OK;
  *         endif
  *         #ccf:State = ACTIVE\\
  *     endif
  *     :Return the Status;
  * stop
  * @enduml
  */ 

/*! \fn hal_status_t HAL_DCACHE_CleanByAddr(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_CleanByAddr:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the Size and the Address;
  *     :Check the HAL DCACHE State is ACTIVE;
  *     if (Flags BUSY or BUSYCMD) then (=1)
  *         #orange: status = HAL_BUSY;
  * 	else (=0)
  *         #ccf:State = MAINTENANCE\\
  *         :DCACHE_CommandByAddr();
  *         :Launch the corresponding DCACHE Command;
  *         if (DCACHE_WaitOnFlagUntilTimeout()) then (===HAL_ERROR)
  *             #red: status = HAL_ERROR;
  *         else (===HAL_OK)
  * 	        #palegreen: status = HAL_OK;
  *         endif
  *         #ccf:State = ACTIVE\\
  *     endif
  *     :Return the Status;
  * stop
  * @enduml
  */ 

/*! \fn hal_status_t HAL_DCACHE_CleanInvalidByAddr(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_CleanInvalidByAddr:
  *
  * @startuml
  * start
  * 	  :Check the HAL DCACHE Handle is not NULL;
  *     :Check the Size and the Address;
  *     :Check the HAL DCACHE State is ACTIVE;
  *     if (Flags BUSY or BUSYCMD) then (=1)
  *         #orange: status = HAL_BUSY;
  * 	else (=0)
  *         #ccf:State = MAINTENANCE\\
  *         :DCACHE_CommandByAddr();
  *         :Launch the corresponding DCACHE Command;
  *         if (DCACHE_WaitOnFlagUntilTimeout()) then (===HAL_ERROR)
  *             #red: status = HAL_ERROR;
  *         else (===HAL_OK)
  * 	        #palegreen: status = HAL_OK;
  *         endif
  *         #ccf:State = ACTIVE\\
  *     endif
  *     :Return the Status;
  * stop
  * @enduml
  */
  
/*! \fn hal_status_t HAL_DCACHE_Invalidate_IT(hal_dcache_handle_t *hdcache);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_Invalidate_IT:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the HAL DCACHE State is ACTIVE;
  *     if (Flags BUSY or BUSYCMD) then (=1)
  *         #orange: return HAL_BUSY;
  *         stop
  * 	else (=0)
  *         #ccf:State = MAINTENANCE\\
  *         :Clear flags BSYEND or CMDEND;
  *         :Set DCACHE Command;
  *         :Enable BSYEND Interrupt;
  *         :Launch DCACHE Invalidation;
  *         #palegreen: return HAL_OK;
  *         stop
  *     endif
  * @enduml
  */  

/*! \fn hal_status_t HAL_DCACHE_InvalidateByAddr_IT(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_InvalidateByAddr_IT:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the Size and the Address;
  *     :Check the HAL DCACHE State is ACTIVE;
  *     if (Flags BUSY or BUSYCMD) then (=1)
  *         #orange: return HAL_BUSY;
  *         stop
  * 	else (=0)
  *         #ccf:State = MAINTENANCE\\  
  *         :DCACHE_CommandByAddr();
  *         :Enable CMDEND Interrupt;
  *         :Launch the corresponding DCACHE Command;
  * 	    #palegreen: return HAL_OK;
  *         stop
  *     endif
  * @enduml
  */   

/*! \fn hal_status_t HAL_DCACHE_CleanByAddr_IT(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_CleanByAddr_IT:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the Size and the Address;
  *     :Check the HAL DCACHE State is ACTIVE;
  *     if (Flags BUSY or BUSYCMD) then (=1)
  *         #orange: return HAL_BUSY;
  *         stop
  * 	else (=0)
  *         #ccf:State = MAINTENANCE\\
  *         :DCACHE_CommandByAddr();
  *         :Enable CMDEND Interrupt;
  *         :Launch the corresponding DCACHE Command;
  * 	    #palegreen: return HAL_OK;
  *         stop
  *     endif
  * @enduml
  */ 

/*! \fn hal_status_t HAL_DCACHE_CleanInvalidByAddr_IT(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_CleanInvalidByAddr_IT:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the Size and the Address;
  *     :Check the HAL DCACHE State is ACTIVE;
  *     if (Flags BUSY or BUSYCMD) then (=1)
  *         #orange: return HAL_BUSY;
  *         stop
  * 	else (=0)
  *         #ccf:State = MAINTENANCE\\
  *         :DCACHE_CommandByAddr();
  *         :Enable CMDEND Interrupt;
  *         :Launch the corresponding DCACHE Command;
  * 	    #palegreen: return HAL_OK;
  *         stop
  *     endif
  * @enduml
  */
  
/*! \fn void HAL_DCACHE_IRQHandler(hal_dcache_handle_t *hdcache);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_IRQHandler:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the DCACHE State is ACTIVE or MAINTENANCE;
  *     if (Error Interrupt Flags) then (=1)
  *         :Clear Error Flag;
  *         :Call the Error Callback with the corresponding error code;
  *     else (=0)
  *     endif
  *     if (BSYEND Interrupt Flags) then (=1)
  *         :Disable BSYEND Interrupt;
  *         :Clear BSYEND Flag;
  *         #ccf:State = ACTIVE\\
  *         :Call the Invalidate Complete Callback;
  *     else (=0)
  *     endif
  *     if (CMDEND Interrupt Flags) then (=1)
  *         :Disable CMDEND Interrupt;
  *         :Clear CMDEND Flag;
  *         #ccf:State = ACTIVE\\
  *         if (DCACHE Command) then (===Clean Invalidate By Address)
  *             :Call the Clean Invalidate By Address Callback;
  *         else if (DCACHE Command) then (===Clean By Address)
  *             :Call the Clean By Address Callback;
  *         else if (DCACHE Command) then (===Invalidate By Address)
  *             :Call the Invalidate By Address Callback;
  *         endif
  *     else (=0)    
  *     endif
  *     stop
  * @enduml
  */

/*! \fn hal_status_t HAL_DCACHE_ErrorCallback(hal_dcache_handle_t *hdcache, hal_dcache_error_code_t error_code);
  * @hidecallergraph
  */
  
/*! \fn hal_status_t HAL_DCACHE_CleanByAddrCallback(hal_dcache_handle_t *hdcache);
  * @hidecallergraph
  */
  
/*! \fn hal_status_t HAL_DCACHE_InvalidateByAddrCallback(hal_dcache_handle_t *hdcache);
  * @hidecallergraph
  */

/*! \fn hal_status_t HAL_DCACHE_CleanInvalidByAddrCallback(hal_dcache_handle_t *hdcache);
  * @hidecallergraph
  */
  
/*! \fn hal_status_t HAL_DCACHE_InvalidateCompleteCallback(hal_dcache_handle_t *hdcache);
  * @hidecallergraph
  */

/*! \fn hal_status_t HAL_DCACHE_RegisterErrorCallback(hal_dcache_handle_t *hdcache, hal_dcache_error_cb_t p_callback);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_RegisterErrorCallback:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the callback error pointer is not NULL;
  *     :Check the HAL DCACHE State is IDLE;
  *     if (Pointer Error Callback) then (=NULL)
  *         #yellow: return HAL_INVALID_PARAM;
  *         stop
  * 	endif
  *     :Set the pointer of the Error Callback to the User's function;
  *     #palegreen: return HAL_OK;
  * stop
  * @enduml
  */
 
/*! \fn hal_status_t HAL_DCACHE_RegisterCleanByAddrCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_RegisterCleanByAddrCallback:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the callback pointer is not NULL;
  *     :Check the HAL DCACHE State is IDLE or ACTIVE;
  *     if (Pointer Callback) then (=NULL)
  *         #yellow: return HAL_INVALID_PARAM;
  *         stop
  * 	endif
  *     :Set the pointer of the corresponding Callback to the User's function;
  *     #palegreen: return HAL_OK;
  * stop
  * @enduml
  */ 

/*! \fn hal_status_t HAL_DCACHE_RegisterInvalidateByAddrCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_RegisterInvalidateByAddrCallback:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the callback pointer is not NULL;
  *     :Check the HAL DCACHE State is IDLE or ACTIVE;
  *     if (Pointer Callback) then (=NULL)
  *         #yellow: return HAL_INVALID_PARAM;
  *         stop
  * 	endif
  *     :Set the pointer of the corresponding Callback to the User's function;
  *     #palegreen: return HAL_OK;
  * stop
  * @enduml
  */ 
  
/*! \fn hal_status_t HAL_DCACHE_RegisterInvalidateCompleteCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_RegisterInvalidateCompleteCallback:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the callback pointer is not NULL;
  *     :Check the HAL DCACHE State is IDLE or ACTIVE;
  *     if (Pointer Callback) then (=NULL)
  *         #yellow: return HAL_INVALID_PARAM;
  *         stop
  * 	endif
  *     :Set the pointer of the corresponding Callback to the User's function;
  *     #palegreen: return HAL_OK;
  * stop
  * @enduml
  */ 
  
/*! \fn hal_status_t HAL_DCACHE_RegisterCleanInvalidByAddrCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_RegisterCleanInvalidByAddrCallback:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the callback pointer is not NULL;
  *     :Check the HAL DCACHE State is IDLE or ACTIVE;
  *     if (Pointer Callback) then (=NULL)
  *         #yellow: return HAL_INVALID_PARAM;
  *         stop
  * 	endif
  *     :Set the pointer of the corresponding Callback to the User's function;
  *     #palegreen: return HAL_OK;
  * stop
  * @enduml
  */

/*! \fn hal_status_t HAL_DCACHE_EnableMonitors(hal_dcache_handle_t *hdcache, uint32_t monitor_type);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_EnableMonitors:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the Monitor(s) Type;
  *     :Check the HAL DCACHE State is IDLE or ACTIVE or MAINTENANCE;
  *     :Enable the Monitor(s);
  *     #palegreen: return HAL_OK;
  * stop
  * @enduml
  */
  
/*! \fn hal_status_t HAL_DCACHE_DisableMonitors(hal_dcache_handle_t *hdcache, uint32_t monitor_type);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_DisableMonitors:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the Monitor(s) Type;
  *     :Check the HAL DCACHE State is IDLE or ACTIVE or MAINTENANCE;
  *     :Disable the Monitor(s);
  *     #palegreen: return HAL_OK;
  * stop
  * @enduml
  */
  
/*! \fn hal_status_t HAL_DCACHE_ResetMonitors(hal_dcache_handle_t *hdcache, uint32_t monitor_type);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_ResetMonitors:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the Monitor(s) Type;
  *     :Check the HAL DCACHE State is IDLE or ACTIVE or MAINTENANCE;
  *     :Reset the Monitor(s);
  *     #palegreen: return HAL_OK;
  * stop
  * @enduml
  */
  
/*! \fn uint32_t HAL_DCACHE_GetMonitorReadHitValue(hal_dcache_handle_t *hdcache);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_GetMonitorReadHitValue:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the HAL DCACHE State is IDLE or ACTIVE or MAINTENANCE;
  *     #palegreen: return the corresponding Monitor Value;
  * stop
  * @enduml
  */
  
/*! \fn uint32_t HAL_DCACHE_GetMonitorReadMissValue(hal_dcache_handle_t *hdcache);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_GetMonitorReadMissValue:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the HAL DCACHE State is IDLE or ACTIVE or MAINTENANCE;
  *     #palegreen: return the corresponding Monitor Value;
  * stop
  * @enduml
  */
  
/*! \fn uint32_t HAL_DCACHE_GetMonitorWriteHitValue(hal_dcache_handle_t *hdcache);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_GetMonitorWriteHitValue:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the HAL DCACHE State is IDLE or ACTIVE or MAINTENANCE;
  *     #palegreen: return the corresponding Monitor Value;
  * stop
  * @enduml
  */
  
/*! \fn uint32_t HAL_DCACHE_GetMonitorWriteMissValue(hal_dcache_handle_t *hdcache);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_GetMonitorWriteMissValue:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     :Check the HAL DCACHE State is IDLE or ACTIVE or MAINTENANCE;
  *     #palegreen: return the corresponding Monitor Value;
  * stop
  * @enduml
  */
  
/*! \fn hal_dcache_state_t HAL_DCACHE_GetState(hal_dcache_handle_t *hdcache);
  * @par Processing
  * The following graph shows the processing of HAL_DCACHE_GetState:
  *
  * @startuml
  * start
  * 	:Check the HAL DCACHE Handle is not NULL;
  *     #palegreen: return the HAL DCACHE State;
  * stop
  * @enduml
  */
  
/*! \fn static void DCACHE_CommandByAddr(hal_dcache_handle_t *hdcache, uint32_t command, uint32_t addr, uint32_t size_byte);
  * @par Processing
  * The following graph shows the processing of DCACHE_CommandByAddr:
  *
  * @startuml
  * start
  *         :Clear flags BSYEND or CMDEND;
  *         :Set DCACHE Start Address;
  *         :Set DCACHE End Address;
  *         :Set DCACHE Command;
  * stop
  * @enduml
  */
  
/*! \fn static hal_status_t DCACHE_WaitOnFlagUntilTimeout(hal_dcache_handle_t *hdcache, uint32_t flag);
  * @par Processing
  * The following graph shows the processing of DCACHE_WaitOnFlagUntilTimeout:
  *
  * @startuml
  * start
  * 	:Call HAL_GetTick to read the current time;
  *     :Wait for end of a DCACHE Command;
  *     while (The specified flag (BSYEND or CMDEND)) is (==0)
  *         if (The waiting time for the end of the operation > 600 ms) then (==Yes)
  *             if (Flags BSYEND or CMDEND) then (==0)
  *                 #red : return HAL_ERROR;
  *                 stop
  *             else (==1)
  *             endif
  *         else (==No)    
  *         endif
  *     endwhile (==1)
  *     #palegreen : return HAL_OK;
  * stop
  * @enduml
  */