/*
 * Do not modify this file; it is automatically generated from the template
 * linkcmd.xdt in the ti.platforms.simplelink package and will be overwritten.
 */

/*
 * put '"'s around paths because, without this, the linker
 * considers '-' as minus operator, not a file name character.
 */


-l"C:\Users\pegor\Desktop\Projects\f91-sw\f91-fw\f91_kepler_app\FlashROM_StackLibrary\configPkg\package\cfg\app_ble_pem3.oem3"
-l"C:\Users\pegor\Desktop\Projects\f91-sw\f91-fw\f91_kepler_app\TOOLS\src\sysbios\rom_sysbios.aem3"
-l"C:\ti\simplelink_cc2640r2_sdk_4_40_00_10\kernel\tirtos\packages\ti\targets\arm\rtsarm\lib\boot.aem3"
-l"C:\ti\simplelink_cc2640r2_sdk_4_40_00_10\kernel\tirtos\packages\ti\targets\arm\rtsarm\lib\auto_init.aem3"
-l"C:\ti\xdctools_3_51_03_28_core\packages\xdc\rov\runtime\lib\xdc.rov.runtime.aem3"

--retain="*(xdc.meta)"

/* C6x Elf symbols */
--symbol_map __TI_STACK_SIZE=__STACK_SIZE
--symbol_map __TI_STACK_BASE=__stack
--symbol_map _stack=__stack


--args 0x0
-heap  0x0
-stack 0x400

/*
 * Linker command file contributions from all loaded packages:
 */

/* Content from xdc.services.global (null): */

/* Content from xdc (null): */

/* Content from xdc.corevers (null): */

/* Content from xdc.rov (null): */

/* Content from xdc.runtime (null): */

/* Content from xdc.rov.runtime (null): */

/* Content from xdc.shelf (null): */

/* Content from xdc.services.spec (null): */

/* Content from xdc.services.intern.xsr (null): */

/* Content from xdc.services.intern.gen (null): */

/* Content from xdc.services.intern.cmd (null): */

/* Content from xdc.bld (null): */

/* Content from ti.targets (null): */

/* Content from ti.targets.arm.elf (null): */

/* Content from ti.targets.arm.rtsarm (null): */

/* Content from ti.sysbios.rom (null): */

/* Content from ti.sysbios.interfaces (null): */

/* Content from ti.sysbios.family (null): */

/* Content from ti.sysbios.family.arm (ti/sysbios/family/arm/linkcmd.xdt): */
--retain "*(.vecs)"

/* Content from xdc.services.getset (null): */

/* Content from ti.sysbios.rts (ti/sysbios/rts/linkcmd.xdt): */

/* Content from xdc.runtime.knl (null): */

/* Content from ti.catalog.arm.cortexm3 (null): */

/* Content from ti.catalog.peripherals.hdvicp2 (null): */

/* Content from ti.catalog (null): */

/* Content from ti.catalog.arm.peripherals.timers (null): */

/* Content from xdc.platform (null): */

/* Content from xdc.cfg (null): */

/* Content from ti.catalog.arm.cortexm4 (null): */

/* Content from ti.platforms.simplelink (null): */

/* Content from ti.sysbios.hal (null): */

/* Content from ti.sysbios.family.arm.cc26xx (null): */

/* Content from ti.sysbios.family.arm.m3 (ti/sysbios/family/arm/m3/linkcmd.xdt): */
-u _c_int00
--retain "*(.resetVecs)"
ti_sysbios_family_arm_m3_Hwi_nvic = 0xe000e000;

/* Content from ti.sysbios.knl (null): */

/* Content from ti.sysbios (null): */

/* Content from ti.sysbios.gates (null): */

/* Content from ti.sysbios.heaps (null): */

/* Content from ti.sysbios.rom.cortexm.cc26xx.r2 (C:/ti/simplelink_cc2640r2_sdk_4_40_00_10/kernel/tirtos/packages/ti/sysbios/rom/cortexm/cc26xx/r2/golden/CC26xx/CC26xx_link_ti.xdt): */

-u xdc_runtime_Error_policy__C
-u xdc_runtime_IModule_Interface__BASE__C
-u xdc_runtime_Startup_lastFxns__C
-u ti_sysbios_knl_Event_Object__DESC__C
-u ti_sysbios_gates_GateMutex_Object__DESC__C
-u ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_initDevice__I
-u xdc_runtime_Startup_execImpl__C
-u ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_getMaxTicks__E
-u ti_sysbios_knl_Swi_Object__count__C
-u ti_sysbios_knl_Idle_funcList__C
-u xdc_runtime_Text_isLoaded__C
-u ti_sysbios_knl_Clock_Object__DESC__C
-u ti_sysbios_knl_Semaphore_eventSync__C
-u ti_sysbios_gates_GateMutex_Module__FXNS__C
-u ti_sysbios_family_arm_m3_Hwi_Module__id__C
-u ti_sysbios_family_arm_cc26xx_Timer_Module__id__C
-u ti_sysbios_knl_Mailbox_Object__table__C
-u ti_sysbios_family_arm_m3_Hwi_Object__table__C
-u ti_sysbios_knl_Swi_Object__DESC__C
-u xdc_runtime_Text_charCnt__C
-u xdc_runtime_Error_raiseHook__C
-u ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_start__E
-u ti_sysbios_heaps_HeapMem_Object__table__C
-u xdc_runtime_Error_policyFxn__C
-u ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_getCount64__E
-u xdc_runtime_Startup_firstFxns__C
-u xdc_runtime_Text_charTab__C
-u ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_TimestampProvider_get32__E
-u xdc_runtime_Error_maxDepth__C
-u ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_getCurrentTick__E
-u ti_sysbios_family_arm_m3_TaskSupport_stackAlignment__C
-u ti_sysbios_family_arm_m3_Hwi_NUM_INTERRUPTS__C
-u ti_sysbios_knl_Clock_triggerClock__C
-u ti_sysbios_knl_Swi_Object__table__C
-u xdc_runtime_Memory_Module__id__C
-u ti_sysbios_heaps_HeapMem_Module__gateObj__C
-u ti_sysbios_family_arm_cc26xx_Timer_startupNeeded__C
-u ti_sysbios_knl_Queue_Object__DESC__C
-u ti_sysbios_knl_Task_Object__DESC__C
-u xdc_runtime_Assert_E_assertFailed__C
-u ti_sysbios_gates_GateHwi_Module__id__C
-u xdc_runtime_IHeap_Interface__BASE__C
-u xdc_runtime_SysCallback_exitFxn__C
-u ti_sysbios_heaps_HeapMem_Module__id__C
-u ti_sysbios_family_arm_m3_Hwi_excHandlerFunc__C
-u ti_sysbios_heaps_HeapMem_Module__FXNS__C
-u xdc_runtime_System_maxAtexitHandlers__C
-u ti_sysbios_knl_Queue_Object__count__C
-u ti_sysbios_knl_Task_Object__table__C
-u ti_sysbios_knl_Mailbox_Object__DESC__C
-u ti_sysbios_family_arm_m3_Hwi_nullIsrFunc__C
-u ti_sysbios_knl_Clock_tickMode__C
-u ti_sysbios_gates_GateMutex_Module__id__C
-u ti_sysbios_knl_Swi_numPriorities__C
-u ti_sysbios_knl_Task_numConstructedTasks__C
-u xdc_runtime_Startup_maxPasses__C
-u ti_sysbios_knl_Task_initStackFlag__C
-u xdc_runtime_System_abortFxn__C
-u ti_sysbios_gates_GateHwi_Module__FXNS__C
-u ti_sysbios_hal_Hwi_Object__DESC__C
-u ti_sysbios_family_arm_m3_Hwi_priGroup__C
-u xdc_runtime_Error_E_memory__C
-u ti_sysbios_family_arm_m3_Hwi_E_alreadyDefined__C
-u ti_sysbios_knl_Queue_Object__table__C
-u ti_sysbios_knl_Semaphore_eventPost__C
-u xdc_runtime_System_exitFxn__C
-u ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_setNextTick__E
-u ti_sysbios_heaps_HeapMem_reqAlign__C
-u xdc_runtime_Startup_sfxnRts__C
-u ti_sysbios_knl_Semaphore_Object__DESC__C
-u ti_sysbios_gates_GateHwi_Object__DESC__C
-u ti_sysbios_heaps_HeapMem_Object__count__C
-u ti_sysbios_family_arm_m3_Hwi_numSparseInterrupts__C
-u ti_sysbios_knl_Mailbox_maxTypeAlign__C
-u ti_sysbios_family_arm_cc26xx_TimestampProvider_useClockTimer__C
-u ti_sysbios_rom_ROM_xdc_runtime_System_SupportProxy_exit__E
-u ti_sysbios_knl_Task_allBlockedFunc__C
-u ti_sysbios_rom_ROM_xdc_runtime_System_SupportProxy_abort__E
-u ti_sysbios_knl_Mailbox_Object__count__C
-u xdc_runtime_Text_nameStatic__C
-u ti_sysbios_rom_ROM_xdc_runtime_Startup_getState__I
-u ti_sysbios_knl_Task_defaultStackSize__C
-u xdc_runtime_IGateProvider_Interface__BASE__C
-u ti_sysbios_family_arm_m3_Hwi_E_hwiLimitExceeded__C
-u xdc_runtime_Startup_startModsFxn__C
-u ti_sysbios_family_arm_m3_Hwi_Object__DESC__C
-u xdc_runtime_Text_nameEmpty__C
-u ti_sysbios_family_arm_m3_Hwi_Object__count__C
-u xdc_runtime_SysCallback_abortFxn__C
-u ti_sysbios_knl_Task_defaultStackHeap__C
-u ti_sysbios_family_arm_m3_Hwi_ccr__C
-u ti_sysbios_heaps_HeapMem_E_memory__C
-u ti_sysbios_knl_Task_Object__count__C
-u ti_sysbios_heaps_HeapMem_Object__DESC__C
-u xdc_runtime_Text_nameUnknown__C
-u xdc_runtime_Memory_defaultHeapInstance__C
-u ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_setThreshold__I
-u xdc_runtime_Startup_sfxnTab__C
-u ti_sysbios_knl_Clock_Module__state__V
-u ti_sysbios_family_arm_cc26xx_TimestampProvider_Module__state__V
-u xdc_runtime_Startup_Module__state__V
-u ti_sysbios_BIOS_Module__state__V
-u ti_sysbios_knl_Swi_Module__state__V
-u ti_sysbios_knl_Task_Module__state__V
-u xdc_runtime_Memory_Module__state__V
-u xdc_runtime_System_Module__state__V
-u ti_sysbios_family_arm_m3_Hwi_Module__state__V
-u xdc_runtime_Error_Module__state__V
-u ti_sysbios_family_arm_cc26xx_Timer_Module__state__V

ti_sysbios_gates_GateMutex_Instance_State_sem__O = 0x1001cb68;
ti_sysbios_family_arm_m3_Hwi_Object__PARAMS__C = 0x1001c9e8;
ti_sysbios_knl_Mailbox_Instance_State_dataQue__O = 0x1001cb74;
ti_sysbios_knl_Task_Module_State_inactiveQ__O = 0x1001cb88;
ti_sysbios_knl_Swi_Object__PARAMS__C = 0x1001ca44;
ti_sysbios_knl_Task_Object__PARAMS__C = 0x1001c978;
ti_sysbios_gates_GateMutex_Object__PARAMS__C = 0x1001caf0;
ti_sysbios_knl_Event_Object__PARAMS__C = 0x1001cb08;
ti_sysbios_heaps_HeapMem_Object__PARAMS__C = 0x1001ca6c;
ti_sysbios_gates_GateHwi_Object__PARAMS__C = 0x1001cad8;
ti_sysbios_knl_Mailbox_Instance_State_dataSem__O = 0x1001cb78;
ti_sysbios_knl_Mailbox_Instance_State_freeSem__O = 0x1001cb80;
ti_sysbios_knl_Semaphore_Object__PARAMS__C = 0x1001cab4;
ti_sysbios_knl_Clock_Object__PARAMS__C = 0x1001ca90;
ti_sysbios_knl_Event_Instance_State_pendQ__O = 0x1001cb70;
ti_sysbios_knl_Queue_Object__PARAMS__C = 0x1001cb20;
ti_sysbios_knl_Clock_Module_State_clockQ__O = 0x1001cb6c;
ti_sysbios_knl_Semaphore_Instance_State_pendQ__O = 0x1001cb84;
ti_sysbios_knl_Mailbox_Object__PARAMS__C = 0x1001c9b4;
ti_sysbios_hal_Hwi_Object__PARAMS__C = 0x1001ca18;
ti_sysbios_rom_cortexm_cc26xx_r2_CC26xx_REVISION__C = 0x10019b00;
ti_sysbios_knl_Mailbox_Instance_State_freeQue__O = 0x1001cb7c;
ti_sysbios_BIOS_RtsGateProxy_query__E = 0x1001c0bd;
ti_sysbios_knl_Queue_get__E = 0x1001bd19;
ti_sysbios_knl_Swi_enabled__E = 0x1001bf21;
ti_sysbios_knl_Clock_scheduleNextTick__E = 0x1001bca9;
ti_sysbios_knl_Swi_runLoop__I = 0x1001adc9;
ti_sysbios_knl_Clock_getTicks__E = 0x1001b29d;
xdc_runtime_Memory_HeapProxy_Object__delete__S = 0x1001ba59;
ti_sysbios_gates_GateMutex_Object__destruct__S = 0x1001b9f9;
ti_sysbios_knl_Queue_enqueue__E = 0x1001bffd;
ti_sysbios_knl_Queue_put__E = 0x1001bd35;
ti_sysbios_family_arm_m3_Hwi_Object__create__S = 0x1001a7b9;
ti_sysbios_gates_GateHwi_Instance_init__E = 0x1001b153;
ti_sysbios_hal_Hwi_Instance_finalize__E = 0x1001c039;
ti_sysbios_BIOS_RtsGateProxy_leave__E = 0x1001c095;
ti_sysbios_heaps_HeapMem_Object__create__S = 0x1001b599;
xdc_runtime_Error_raiseX__E = 0x1001c66d;
ti_sysbios_hal_Hwi_getStackInfo__E = 0x1001b099;
ti_sysbios_knl_Semaphore_construct = 0x1001b45d;
ti_sysbios_knl_Clock_Object__destruct__S = 0x1001ba99;
ti_sysbios_knl_Clock_TimerProxy_getMaxTicks__E = 0x1001bef1;
ti_sysbios_knl_Swi_Object__destruct__S = 0x1001bd51;
ti_sysbios_family_arm_cc26xx_TimestampProvider_getFreq__E = 0x1001bf6b;
ti_sysbios_gates_GateMutex_Handle__label__S = 0x1001b9d9;
ti_sysbios_knl_Mailbox_delete = 0x1001c0f1;
ti_sysbios_knl_Semaphore_destruct = 0x1001c10d;
ti_sysbios_BIOS_RtsGateProxy_enter__E = 0x1001c091;
ti_sysbios_knl_Task_processVitalTaskFlag__I = 0x1001b48d;
ti_sysbios_knl_Mailbox_create = 0x1001a945;
xdc_runtime_Core_deleteObject__I = 0x1001c3b5;
ti_sysbios_knl_Queue_delete = 0x1001c0f9;
ti_sysbios_family_arm_m3_Hwi_doSwiRestore__I = 0x1001c043;
xdc_runtime_Timestamp_getFreq__E = 0x1001bf6b;
ti_sysbios_knl_Event_Instance_init__E = 0x1001be49;
xdc_runtime_System_atexit__E = 0x1001c581;
ti_sysbios_gates_GateMutex_Params__init__S = 0x1001bfb5;
ti_sysbios_knl_Clock_getTimerHandle__E = 0x1001bfcd;
ti_sysbios_knl_Task_enable__E = 0x1001c08b;
ti_sysbios_knl_Clock_TimerProxy_getExpiredTicks__E = 0x1001c0d1;
xdc_runtime_Timestamp_SupportProxy_get64__E = 0x1001b77d;
ti_sysbios_knl_Queue_Object__destruct__S = 0x1001bcfd;
ti_sysbios_knl_Clock_Object__delete__S = 0x1001b8b1;
ti_sysbios_gates_GateMutex_delete = 0x1001c0b5;
ti_sysbios_heaps_HeapMem_restore__E = 0x1001bf41;
ti_sysbios_BIOS_RtsGateProxy_Object__delete__S = 0x1001b88d;
ti_sysbios_knl_Swi_create = 0x1001ac1d;
ti_sysbios_heaps_HeapMem_Module_GateProxy_leave__E = 0x1001c0cd;
ti_sysbios_knl_Semaphore_pend__E = 0x10019b05;
ti_sysbios_knl_Mailbox_Instance_finalize__E = 0x1001a4c5;
xdc_runtime_Startup_startMods__I = 0x1001c129;
ti_sysbios_heaps_HeapMem_init__I = 0x1001b235;
ti_sysbios_knl_Swi_Object__delete__S = 0x1001bbb9;
ti_sysbios_hal_Hwi_HwiProxy_enableInterrupt__E = 0x1001af89;
ti_sysbios_knl_Clock_removeI__E = 0x1001c0e1;
xdc_runtime_System_abort__E = 0x1001c64d;
ti_sysbios_family_arm_m3_Hwi_dispatchC__I = 0x1001a81d;
ti_sysbios_knl_Swi_construct = 0x1001ad79;
ti_sysbios_knl_Task_sleepTimeout__I = 0x1001bda5;
ti_sysbios_knl_Queue_remove__E = 0x1001bf5d;
ti_sysbios_knl_Semaphore_Instance_finalize__E = 0x1001b7cd;
ti_sysbios_gates_GateMutex_destruct = 0x1001c0b9;
ti_sysbios_knl_Task_SupportProxy_Module__startupDone__S = 0x1001c0ad;
ti_sysbios_knl_Queue_Object__delete__S = 0x1001bb59;
ti_sysbios_knl_Mailbox_Object__get__S = 0x1001b649;
ti_sysbios_family_arm_m3_Hwi_Instance_init__E = 0x10019fc1;
ti_sysbios_knl_Clock_delete = 0x1001c0d9;
ti_sysbios_knl_Clock_walkQueueDynamic__E = 0x1001a2f1;
ti_sysbios_knl_Mailbox_Object__destruct__S = 0x1001bce1;
ti_sysbios_knl_Mailbox_post__E = 0x1001a0ed;
ti_sysbios_knl_Clock_Instance_init__E = 0x1001b1c5;
ti_sysbios_knl_Event_construct = 0x1001b5f1;
ti_sysbios_knl_Task_allBlockedFunction__I = 0x1001b055;
ti_sysbios_knl_Task_postInit__I = 0x1001a271;
ti_sysbios_knl_Task_enter__I = 0x1001bd89;
ti_sysbios_hal_Hwi_switchFromBootStack__E = 0x1001be35;
ti_sysbios_knl_Semaphore_Object__destruct__S = 0x1001bb99;
ti_sysbios_hal_Hwi_HwiProxy_Object__create__S = 0x1001bed1;
ti_sysbios_family_arm_cc26xx_Timer_postInit__I = 0x1001b4bd;
ti_sysbios_knl_Swi_Module_startup__E = 0x1001c07f;
ti_sysbios_gates_GateMutex_Instance_finalize__E = 0x1001bec1;
ti_sysbios_hal_Hwi_startup__E = 0x1001c04b;
xdc_runtime_Core_assignParams__I = 0x1001c4ad;
ti_sysbios_hal_Hwi_HwiProxy_switchFromBootStack__E = 0x1001be35;
//ti_sysbios_heaps_HeapMem_allocUnprotected__E = 0x1001a615;
ti_sysbios_knl_Swi_post__E = 0x1001b011;
ti_sysbios_hal_Hwi_initStack = 0x1001b56d;
xdc_runtime_Memory_alloc__E = 0x1001c349;
ti_sysbios_knl_Queue_next__E = 0x1001c105;
ti_sysbios_knl_Event_destruct = 0x1001c0ed;
ti_sysbios_knl_Clock_Instance_finalize__E = 0x1001be09;
ti_sysbios_knl_Queue_elemClear__E = 0x1001c079;
ti_sysbios_knl_Clock_TimerProxy_startup__E = 0x1001b4e9;
ti_sysbios_knl_Clock_Params__init__S = 0x1001bfc1;
ti_sysbios_knl_Task_Instance_init__E = 0x10019ce1;
ti_sysbios_hal_Hwi_HwiProxy_startup__E = 0x1001c04b;
ti_sysbios_knl_Task_self__E = 0x1001c02d;
ti_sysbios_knl_Task_startup__E = 0x1001c125;
ti_sysbios_gates_GateHwi_Object__delete__S = 0x1001b9b9;
ti_sysbios_family_arm_cc26xx_Timer_startup__E = 0x1001b4e9;
xdc_runtime_Memory_free__E = 0x1001c705;
ti_sysbios_knl_Clock_triggerFunc__I = 0x1001bdbf;
ti_sysbios_hal_Hwi_delete = 0x1001c0c5;
ti_sysbios_knl_Queue_Instance_init__E = 0x1001c073;
ti_sysbios_knl_Event_delete = 0x1001c0e9;
ti_sysbios_BIOS_RtsGateProxy_Handle__label__S = 0x1001b9d9;
ti_sysbios_family_arm_cc26xx_Timer_Module_startup__E = 0x1001b845;
ti_sysbios_knl_Event_Object__delete__S = 0x1001bad9;
xdc_runtime_Assert_raise__I = 0x1001c465;
ti_sysbios_hal_Hwi_create = 0x1001a881;
ti_sysbios_knl_Task_destruct = 0x1001c121;
ti_sysbios_hal_Hwi_Module_startup__E = 0x1001be5d;
ti_sysbios_family_arm_m3_Hwi_excHandler__I = 0x1001b979;
xdc_runtime_Core_destructObject__I = 0x1001c6a5;
ti_sysbios_knl_Swi_disable__E = 0x1001bf11;
ti_sysbios_BIOS_setThreadType__E = 0x1001bea1;
ti_sysbios_knl_Task_disable__E = 0x1001bf31;
ti_sysbios_knl_Swi_Instance_init__E = 0x1001a9a5;
ti_sysbios_knl_Semaphore_pendTimeout__I = 0x1001b6f9;
ti_sysbios_knl_Clock_create = 0x1001b1fd;
ti_sysbios_knl_Idle_loop__E = 0x1001c053;
ti_sysbios_gates_GateHwi_leave__E = 0x1001c067;
ti_sysbios_family_arm_m3_Hwi_enableInterrupt__E = 0x1001af89;
ti_sysbios_knl_Semaphore_Params__init__S = 0x1001c009;
ti_sysbios_knl_Event_pend__E = 0x10019bf9;
ti_sysbios_knl_Task_unblock__E = 0x1001bdf1;
ti_sysbios_knl_Swi_destruct = 0x1001c115;
ti_sysbios_knl_Event_sync__E = 0x1001be6f;
ti_sysbios_BIOS_getCpuFreq__E = 0x1001be91;
xdc_runtime_Memory_calloc__E = 0x1001c751;
ti_sysbios_family_arm_m3_Hwi_startup__E = 0x1001c04b;
xdc_runtime_System_Module_GateProxy_Handle__label__S = 0x1001b999;
xdc_runtime_SysCallback_exit__E = 0x1001c725;
ti_sysbios_hal_Hwi_HwiProxy_Params__init__S = 0x1001bf79;
ti_sysbios_knl_Queue_empty__E = 0x1001bf4f;
ti_sysbios_knl_Clock_logTick__E = 0x1001b843;
ti_sysbios_knl_Event_Params__init__S = 0x1001bfd9;
ti_sysbios_knl_Task_yield__E = 0x1001b0d9;
ti_sysbios_knl_Task_SupportProxy_getStackAlignment__E = 0x1001bf9d;
ti_sysbios_family_arm_m3_Hwi_create = 0x1001a8e5;
xdc_runtime_Timestamp_SupportProxy_get32__E = 0x1001c735;
ti_sysbios_family_arm_m3_Hwi_destruct = 0x1001c0a9;
xdc_runtime_Timestamp_get32__E = 0x1001c735;
ti_sysbios_knl_Clock_stop__E = 0x1001bab9;
ti_sysbios_family_arm_m3_Hwi_doTaskRestore__I = 0x1001c05b;
ti_sysbios_BIOS_linkedWithIncorrectBootLibrary__E = 0x1001a683;
ti_sysbios_knl_Swi_run__I = 0x1001ac75;
ti_sysbios_family_arm_cc26xx_Timer_Module__startupDone__S = 0x1001b8f9;
xdc_runtime_Core_createObject__I = 0x1001c2c9;
ti_sysbios_knl_Queue_create = 0x1001b6cd;
ti_sysbios_hal_Hwi_Object__delete__S = 0x1001ba19;
ti_sysbios_knl_Clock_construct = 0x1001b269;
xdc_runtime_System_abortSpin__E = 0x1001c7a1;
ti_sysbios_family_arm_m3_Hwi_Object__destruct__S = 0x1001bc39;
ti_sysbios_hal_Hwi_HwiProxy_delete = 0x1001c0c1;
ti_sysbios_gates_GateMutex_Object__create__S = 0x1001b36d;
ti_sysbios_family_arm_m3_Hwi_getStackInfo__E = 0x1001b099;
ti_sysbios_heaps_HeapMem_Module_GateProxy_enter__E = 0x1001c0c9;
ti_sysbios_knl_Semaphore_post__E = 0x1001a3e1;
ti_sysbios_knl_Task_exit__E = 0x1001b119;
ti_sysbios_heaps_HeapMem_Instance_init__E = 0x1001b18d;
ti_sysbios_knl_Swi_restore__E = 0x1001b305;
ti_sysbios_knl_Task_startCore__E = 0x1001aa61;
ti_sysbios_knl_Semaphore_create = 0x1001b2d1;
ti_sysbios_gates_GateHwi_enter__E = 0x1001bfa9;
ti_sysbios_knl_Task_blockI__E = 0x1001b339;
ti_sysbios_heaps_HeapMem_free__E = 0x1001b3fd;
ti_sysbios_knl_Task_Object__destruct__S = 0x1001bd6d;
ti_sysbios_hal_Hwi_enableInterrupt__E = 0x1001af89;
ti_sysbios_family_arm_cc26xx_Timer_periodicStub__E = 0x10019f25;
ti_sysbios_hal_Hwi_Instance_init__E = 0x1001b81d;
ti_sysbios_gates_GateHwi_query__E = 0x1001c0b1;
xdc_runtime_System_processAtExit__E = 0x1001c5ed;
ti_sysbios_family_arm_cc26xx_Timer_setPeriod__E = 0x1001c0a1;
/* xdc_runtime_Error_init__E = 0x1001c745; */
ti_sysbios_knl_Semaphore_Instance_init__E = 0x1001a685;
xdc_runtime_System_Module_GateProxy_Object__delete__S = 0x1001b9b9;
xdc_runtime_Memory_HeapProxy_Handle__label__S = 0x1001ba39;
ti_sysbios_knl_Queue_head__E = 0x1001c101;
xdc_runtime_Timestamp_SupportProxy_getFreq__E = 0x1001bf6b;
xdc_runtime_Error_check__E = 0x1001c6bd;
xdc_runtime_Error_policySpin__E = 0x1001c413;
ti_sysbios_gates_GateMutex_create = 0x1001b39d;
xdc_runtime_Gate_leaveSystem__E = 0x1001c789;
ti_sysbios_knl_Swi_restoreHwi__E = 0x1001a6ed;
ti_sysbios_knl_Task_sleep__E = 0x1001a5a5;
/* xdc_runtime_Error_policyDefault__E = 0x1001c221; */
ti_sysbios_knl_Task_create = 0x1001accd;
ti_sysbios_knl_Mailbox_Params__init__S = 0x1001bfe5;
ti_sysbios_knl_Task_restoreHwi__E = 0x1001bc19;
ti_sysbios_knl_Mailbox_postInit__I = 0x1001b675;
ti_sysbios_knl_Task_delete = 0x1001c11d;
ti_sysbios_heaps_HeapMem_isBlocking__E = 0x1001c06d;
ti_sysbios_knl_Clock_startI__E = 0x1001a1f1;
ti_sysbios_knl_Clock_start__E = 0x1001be1f;
ti_sysbios_heaps_HeapMem_Module_GateProxy_query__E = 0x1001c0bd;
ti_sysbios_family_arm_m3_Hwi_Object__delete__S = 0x1001b959;
ti_sysbios_knl_Clock_TimerProxy_getPeriod__E = 0x1001c0d5;
ti_sysbios_knl_Event_checkEvents__I = 0x1001baf9;
ti_sysbios_knl_Task_SupportProxy_start__E = 0x1001b155;
ti_sysbios_heaps_HeapMem_Handle__label__S = 0x1001ba39;
ti_sysbios_family_arm_m3_Hwi_delete = 0x1001c0a5;
ti_sysbios_heaps_HeapMem_Module_GateProxy_Handle__label__S = 0x1001b9d9;
ti_sysbios_knl_Semaphore_Object__delete__S = 0x1001b8d5;
ti_sysbios_hal_Hwi_HwiProxy_getStackInfo__E = 0x1001b099;
ti_sysbios_knl_Idle_run__E = 0x1001bb19;
ti_sysbios_knl_Swi_delete = 0x1001c111;
xdc_runtime_Memory_valloc__E = 0x1001c689;
ti_sysbios_knl_Mailbox_Object__delete__S = 0x1001bb39;
ti_sysbios_family_arm_m3_TaskSupport_start__E = 0x1001b155;
xdc_runtime_Timestamp_get64__E = 0x1001b77d;
ti_sysbios_family_arm_m3_Hwi_Module__startupDone__S = 0x1001b939;
ti_sysbios_heaps_HeapMem_Module_GateProxy_Params__init__S = 0x1001bfb5;
ti_sysbios_knl_Swi_startup__E = 0x1001c085;
ti_sysbios_knl_Task_schedule__I = 0x1001ae69;
ti_sysbios_gates_GateMutex_leave__E = 0x1001bdd9;
ti_sysbios_heaps_HeapMem_Object__delete__S = 0x1001ba59;
ti_sysbios_knl_Event_create = 0x1001b42d;
/* xdc_runtime_Error_setX__E = 0x1001c53d; */
ti_sysbios_knl_Clock_TimerProxy_setNextTick__E = 0x1001bf01;
ti_sysbios_knl_Swi_Object__get__S = 0x1001b725;
ti_sysbios_knl_Task_restore__E = 0x1001b7f5;
xdc_runtime_Memory_HeapProxy_alloc__E = 0x1001c775;
ti_sysbios_heaps_HeapMem_Module_GateProxy_Object__delete__S = 0x1001b88d;
ti_sysbios_gates_GateHwi_Object__create__S = 0x1001b869;
ti_sysbios_hal_Hwi_HwiProxy_disableInterrupt__E = 0x1001af45;
ti_sysbios_BIOS_start__E = 0x1001beb1;
ti_sysbios_BIOS_exit__E = 0x1001be81;
ti_sysbios_family_arm_m3_TaskSupport_getStackAlignment__E = 0x1001bf9d;
xdc_runtime_SysCallback_abort__E = 0x1001c715;
ti_sysbios_knl_Queue_destruct = 0x1001c0fd;
ti_sysbios_family_arm_m3_Hwi_postInit__I = 0x10019e75;
ti_sysbios_gates_GateMutex_Instance_init__E = 0x1001bc71;
ti_sysbios_knl_Task_Instance_finalize__E = 0x1001a059;
ti_sysbios_knl_Clock_TimerProxy_getCurrentTick__E = 0x1001bee1;
ti_sysbios_family_arm_m3_Hwi_disableFxn__E = 0x1001bf85;
xdc_runtime_Memory_HeapProxy_free__E = 0x1001c77f;
ti_sysbios_knl_Mailbox_Module_startup__E = 0x1001afcd;
ti_sysbios_knl_Task_Object__delete__S = 0x1001bbd9;
xdc_runtime_Startup_rtsDone__E = 0x1001c769;
ti_sysbios_gates_GateHwi_Handle__label__S = 0x1001b999;
xdc_runtime_Text_ropeText__E = 0x1001c6ed;
ti_sysbios_knl_Clock_destruct = 0x1001c0dd;
ti_sysbios_knl_Queue_construct = 0x1001b6a1;
ti_sysbios_family_arm_m3_Hwi_switchFromBootStack__E = 0x1001be35;
ti_sysbios_heaps_HeapMem_Object__get__S = 0x1001b5c5;
ti_sysbios_hal_Hwi_HwiProxy_create = 0x1001bc8d;
ti_sysbios_gates_GateMutex_query__E = 0x1001c0bd;
ti_sysbios_knl_Swi_schedule__I = 0x1001ad25;
ti_sysbios_knl_Task_Params__init__S = 0x1001c021;
ti_sysbios_family_arm_m3_Hwi_Params__init__S = 0x1001bf79;
ti_sysbios_family_arm_m3_Hwi_plug__E = 0x1001bdc1;
xdc_runtime_System_exitSpin__E = 0x1001c7a3;
xdc_runtime_System_Module_GateProxy_query__E = 0x1001c0b1;
ti_sysbios_gates_GateMutex_construct = 0x1001b541;
xdc_runtime_System_Module_GateProxy_leave__E = 0x1001c79d;
ti_sysbios_knl_Mailbox_pend__E = 0x1001a535;
ti_sysbios_hal_Hwi_HwiProxy_Object__delete__S = 0x1001b959;
ti_sysbios_family_arm_m3_TaskSupport_Module__startupDone__S = 0x1001c0ad;
ti_sysbios_BIOS_RtsGateProxy_Params__init__S = 0x1001bfb5;
xdc_runtime_Core_assignLabel__I = 0x1001c5b9;
ti_sysbios_heaps_HeapMem_freeUnprotected__E = 0x1001ab6d;
xdc_runtime_System_Module_GateProxy_enter__E = 0x1001c799;
xdc_runtime_System_exit__E = 0x1001c6d5;
ti_sysbios_knl_Swi_Params__init__S = 0x1001c015;
ti_sysbios_knl_Event_Object__destruct__S = 0x1001bcc5;
ti_sysbios_knl_Clock_workFunc__E = 0x1001a369;
ti_sysbios_family_arm_m3_Hwi_restoreFxn__E = 0x1001c061;
ti_sysbios_family_arm_cc26xx_TimestampProvider_Module_startup__E = 0x1001b919;
ti_sysbios_knl_Semaphore_delete = 0x1001c109;
ti_sysbios_family_arm_cc26xx_Timer_getPeriod__E = 0x1001c09d;
ti_sysbios_family_arm_m3_Hwi_initNVIC__E = 0x1001a171;
ti_sysbios_knl_Clock_addI__E = 0x1001b7a5;
ti_sysbios_family_arm_m3_Hwi_Instance_finalize__E = 0x1001a755;
//ti_sysbios_heaps_HeapMem_alloc__E = 0x1001ab15;
ti_sysbios_knl_Task_unblockI__E = 0x1001b751;
ti_sysbios_knl_Swi_Instance_finalize__E = 0x1001bf77;
ti_sysbios_family_arm_m3_Hwi_disableInterrupt__E = 0x1001af45;
ti_sysbios_family_arm_m3_Hwi_enableFxn__E = 0x1001bf91;
xdc_runtime_Gate_enterSystem__E = 0x1001c795;
ti_sysbios_gates_GateMutex_Object__delete__S = 0x1001b88d;
ti_sysbios_family_arm_cc26xx_TimestampProvider_get64__E = 0x1001b77d;
ti_sysbios_knl_Mailbox_Instance_init__E = 0x10019dad;
xdc_runtime_Text_cordText__E = 0x1001c621;
xdc_runtime_Startup_exec__E = 0x1001c415;
ti_sysbios_hal_Hwi_HwiProxy_Module__startupDone__S = 0x1001b939;
ti_sysbios_heaps_HeapMem_getStats__E = 0x1001aefd;
xdc_runtime_Memory_getMaxDefaultTypeAlign__E = 0x1001c75d;
ti_sysbios_hal_Hwi_disableInterrupt__E = 0x1001af45;
ti_sysbios_knl_Event_post__E = 0x1001a455;
ti_sysbios_knl_Task_Object__get__S = 0x1001bbf9;
ti_sysbios_knl_Event_pendTimeout__I = 0x1001b61d;
ti_sysbios_family_arm_m3_Hwi_construct = 0x1001aabd;
ti_sysbios_knl_Clock_TimerProxy_Module__startupDone__S = 0x1001b8f9;
ti_sysbios_knl_Clock_Module_startup__E = 0x1001ba79;
ti_sysbios_knl_Mailbox_construct = 0x1001abc5;
ti_sysbios_knl_Task_construct = 0x1001ae19;
xdc_runtime_Core_constructObject__I = 0x1001c4f5;
ti_sysbios_knl_Queue_dequeue__E = 0x1001bff1;
ti_sysbios_knl_Task_Module_startup__E = 0x1001aa05;
ti_sysbios_family_arm_cc26xx_Timer_getExpiredTicks__E = 0x1001c099;
ti_sysbios_family_arm_m3_Hwi_Object__get__S = 0x1001b515;
ti_sysbios_knl_Mailbox_destruct = 0x1001c0f5;
xdc_runtime_System_Module_startup__E = 0x1001c78f;
ti_sysbios_knl_Swi_postInit__I = 0x1001c119;
ti_sysbios_family_arm_m3_Hwi_Module_startup__E = 0x1001aeb5;
ti_sysbios_gates_GateMutex_enter__E = 0x1001b3cd;
ti_sysbios_family_arm_m3_Hwi_setPriority__E = 0x1001bc55;
ti_sysbios_knl_Queue_Object__get__S = 0x1001bb79;
ti_sysbios_knl_Clock_setTimeout__E = 0x1001c0e5;
ti_sysbios_family_arm_m3_Hwi_excHandlerAsm__I = 0x1001c901;
ti_sysbios_family_arm_m3_Hwi_return = 0x1001c957;
ti_sysbios_family_arm_m3_Hwi_pendSV__I = 0x1001c93f;
ti_sysbios_family_arm_m3_Hwi_dispatch__I = 0x1001c7a5;
ti_sysbios_family_xxx_Hwi_switchAndRunFunc = 0x1001c921;
ti_sysbios_family_arm_m3_Hwi_initStacks__E = 0x1001c8b9;
ti_sysbios_knl_Task_swapReturn = 0x1001c971;
ti_sysbios_family_arm_m3_TaskSupport_glue = 0x1001c959;
ti_sysbios_family_arm_m3_TaskSupport_buildTaskStack = 0x1001c86d;
ti_sysbios_family_arm_m3_TaskSupport_swap__E = 0x1001c969;
ti_sysbios_knl_Task_SupportProxy_swap__E = 0x1001c969;

SECTIONS
{
    .const:xdc_runtime_Error_policy__C: LOAD > 0x00001300
    .const:xdc_runtime_IModule_Interface__BASE__C: LOAD > 0x000012b8
    .const:xdc_runtime_Startup_lastFxns__C: LOAD > 0x00001298
    .const:ti_sysbios_knl_Event_Object__DESC__C: LOAD > 0x00001130
    .const:ti_sysbios_gates_GateMutex_Object__DESC__C: LOAD > 0x000010b0
    .const:ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_initDevice__I: LOAD > 0x00001310
    .const:xdc_runtime_Startup_execImpl__C: LOAD > 0x000012c0
    .const:ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_getMaxTicks__E: LOAD > 0x0000130c
    .const:ti_sysbios_knl_Swi_Object__count__C: LOAD > 0x0000125c
    .const:ti_sysbios_knl_Idle_funcList__C: LOAD > 0x000011f0
    .const:xdc_runtime_Text_isLoaded__C: LOAD > 0x000012fe
    .const:ti_sysbios_knl_Clock_Object__DESC__C: LOAD > 0x00001110
    .const:ti_sysbios_knl_Semaphore_eventSync__C: LOAD > 0x00001258
    .const:ti_sysbios_gates_GateMutex_Module__FXNS__C: LOAD > 0x0000104c
    .const:ti_sysbios_family_arm_m3_Hwi_Module__id__C: LOAD > 0x00001284
    .const:ti_sysbios_family_arm_cc26xx_Timer_Module__id__C: LOAD > 0x00001280
    .const:ti_sysbios_knl_Mailbox_Object__table__C: LOAD > 0x00001244
    .const:ti_sysbios_family_arm_m3_Hwi_Object__table__C: LOAD > 0x0000120c
    .const:ti_sysbios_knl_Swi_Object__DESC__C: LOAD > 0x000011b0
    .const:xdc_runtime_Text_charCnt__C: LOAD > 0x000012fc
    .const:xdc_runtime_Error_raiseHook__C: LOAD > 0x000012ac
    .const:ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_start__E: LOAD > 0x0000131c
    .const:ti_sysbios_heaps_HeapMem_Object__table__C: LOAD > 0x00001234
    .const:xdc_runtime_Error_policyFxn__C: LOAD > 0x000012a8
    .const:ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_getCount64__E: LOAD > 0x00001304
    .const:xdc_runtime_Startup_firstFxns__C: LOAD > 0x00001290
    .const:xdc_runtime_Text_charTab__C: LOAD > 0x000012e8
    .const:ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_TimestampProvider_get32__E: LOAD > 0x00001320
    .const:xdc_runtime_Error_maxDepth__C: LOAD > 0x000012f8
    .const:ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_getCurrentTick__E: LOAD > 0x00001308
    .const:ti_sysbios_family_arm_m3_TaskSupport_stackAlignment__C: LOAD > 0x00001224
    .const:ti_sysbios_family_arm_m3_Hwi_NUM_INTERRUPTS__C: LOAD > 0x00001204
    .const:ti_sysbios_knl_Clock_triggerClock__C: LOAD > 0x0000123c
    .const:ti_sysbios_knl_Swi_Object__table__C: LOAD > 0x00001260
    .const:xdc_runtime_Memory_Module__id__C: LOAD > 0x000012fa
    .const:ti_sysbios_heaps_HeapMem_Module__gateObj__C: LOAD > 0x0000122c
    .const:ti_sysbios_family_arm_cc26xx_Timer_startupNeeded__C: LOAD > 0x000011f8
    .const:ti_sysbios_knl_Queue_Object__DESC__C: LOAD > 0x00001170
    .const:ti_sysbios_knl_Task_Object__DESC__C: LOAD > 0x000011d0
    .const:xdc_runtime_Assert_E_assertFailed__C: LOAD > 0x000012a0
    .const:ti_sysbios_gates_GateHwi_Module__id__C: LOAD > 0x00001286
    .const:xdc_runtime_IHeap_Interface__BASE__C: LOAD > 0x000012b4
    .const:xdc_runtime_SysCallback_exitFxn__C: LOAD > 0x000012d8
    .const:ti_sysbios_heaps_HeapMem_Module__id__C: LOAD > 0x0000128a
    .const:ti_sysbios_family_arm_m3_Hwi_excHandlerFunc__C: LOAD > 0x00001214
    .const:ti_sysbios_heaps_HeapMem_Module__FXNS__C: LOAD > 0x00001000
    .const:xdc_runtime_System_maxAtexitHandlers__C: LOAD > 0x000012e4
    .const:ti_sysbios_knl_Queue_Object__count__C: LOAD > 0x0000124c
    .const:ti_sysbios_knl_Task_Object__table__C: LOAD > 0x0000126c
    .const:ti_sysbios_knl_Mailbox_Object__DESC__C: LOAD > 0x00001150
    .const:ti_sysbios_family_arm_m3_Hwi_nullIsrFunc__C: LOAD > 0x00001218
    .const:ti_sysbios_knl_Clock_tickMode__C: LOAD > 0x0000128e
    .const:ti_sysbios_gates_GateMutex_Module__id__C: LOAD > 0x00001288
    .const:ti_sysbios_knl_Swi_numPriorities__C: LOAD > 0x00001264
    .const:ti_sysbios_knl_Task_numConstructedTasks__C: LOAD > 0x0000127c
    .const:xdc_runtime_Startup_maxPasses__C: LOAD > 0x000012c4
    .const:ti_sysbios_knl_Task_initStackFlag__C: LOAD > 0x0000128c
    .const:xdc_runtime_System_abortFxn__C: LOAD > 0x000012dc
    .const:ti_sysbios_gates_GateHwi_Module__FXNS__C: LOAD > 0x00001028
    .const:ti_sysbios_hal_Hwi_Object__DESC__C: LOAD > 0x000010d0
    .const:ti_sysbios_family_arm_m3_Hwi_priGroup__C: LOAD > 0x00001220
    .const:xdc_runtime_Error_E_memory__C: LOAD > 0x000012a4
    .const:ti_sysbios_family_arm_m3_Hwi_E_alreadyDefined__C: LOAD > 0x000011fc
    .const:ti_sysbios_knl_Queue_Object__table__C: LOAD > 0x00001250
    .const:ti_sysbios_knl_Semaphore_eventPost__C: LOAD > 0x00001254
    .const:xdc_runtime_System_exitFxn__C: LOAD > 0x000012e0
    .const:ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_setNextTick__E: LOAD > 0x00001314
    .const:ti_sysbios_heaps_HeapMem_reqAlign__C: LOAD > 0x00001238
    .const:xdc_runtime_Startup_sfxnRts__C: LOAD > 0x000012c8
    .const:ti_sysbios_knl_Semaphore_Object__DESC__C: LOAD > 0x00001190
    .const:ti_sysbios_gates_GateHwi_Object__DESC__C: LOAD > 0x00001090
    .const:ti_sysbios_heaps_HeapMem_Object__count__C: LOAD > 0x00001230
    .const:ti_sysbios_family_arm_m3_Hwi_numSparseInterrupts__C: LOAD > 0x0000121c
    .const:ti_sysbios_knl_Mailbox_maxTypeAlign__C: LOAD > 0x00001248
    .const:ti_sysbios_family_arm_cc26xx_TimestampProvider_useClockTimer__C: LOAD > 0x00001282
    .const:ti_sysbios_rom_ROM_xdc_runtime_System_SupportProxy_exit__E: LOAD > 0x0000132c
    .const:ti_sysbios_knl_Task_allBlockedFunc__C: LOAD > 0x00001270
    .const:ti_sysbios_rom_ROM_xdc_runtime_System_SupportProxy_abort__E: LOAD > 0x00001328
    .const:ti_sysbios_knl_Mailbox_Object__count__C: LOAD > 0x00001240
    .const:xdc_runtime_Text_nameStatic__C: LOAD > 0x000012f0
    .const:ti_sysbios_rom_ROM_xdc_runtime_Startup_getState__I: LOAD > 0x00001324
    .const:ti_sysbios_knl_Task_defaultStackSize__C: LOAD > 0x00001278
    .const:xdc_runtime_IGateProvider_Interface__BASE__C: LOAD > 0x000012b0
    .const:ti_sysbios_family_arm_m3_Hwi_E_hwiLimitExceeded__C: LOAD > 0x00001200
    .const:xdc_runtime_Startup_startModsFxn__C: LOAD > 0x000012d0
    .const:ti_sysbios_family_arm_m3_Hwi_Object__DESC__C: LOAD > 0x00001070
    .const:xdc_runtime_Text_nameEmpty__C: LOAD > 0x000012ec
    .const:ti_sysbios_family_arm_m3_Hwi_Object__count__C: LOAD > 0x00001208
    .const:xdc_runtime_SysCallback_abortFxn__C: LOAD > 0x000012d4
    .const:ti_sysbios_knl_Task_defaultStackHeap__C: LOAD > 0x00001274
    .const:ti_sysbios_family_arm_m3_Hwi_ccr__C: LOAD > 0x00001210
    .const:ti_sysbios_heaps_HeapMem_E_memory__C: LOAD > 0x00001228
    .const:ti_sysbios_knl_Task_Object__count__C: LOAD > 0x00001268
    .const:ti_sysbios_heaps_HeapMem_Object__DESC__C: LOAD > 0x000010f0
    .const:xdc_runtime_Text_nameUnknown__C: LOAD > 0x000012f4
    .const:xdc_runtime_Memory_defaultHeapInstance__C: LOAD > 0x000012bc
    .const:ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_setThreshold__I: LOAD > 0x00001318
    .const:xdc_runtime_Startup_sfxnTab__C: LOAD > 0x000012cc
    .data:ti_sysbios_knl_Clock_Module__state__V: LOAD > 0x20000178
    .data:ti_sysbios_family_arm_cc26xx_TimestampProvider_Module__state__V: LOAD > 0x200001ec
    .data:xdc_runtime_Startup_Module__state__V: LOAD > 0x200001f0
    .data:ti_sysbios_BIOS_Module__state__V: LOAD > 0x200001a4
    .data:ti_sysbios_knl_Swi_Module__state__V: LOAD > 0x200001c8
    .data:ti_sysbios_knl_Task_Module__state__V: LOAD > 0x20000100
    .data:xdc_runtime_Memory_Module__state__V: LOAD > 0x20000200
    .data:xdc_runtime_System_Module__state__V: LOAD > 0x200001f8
    .data:ti_sysbios_family_arm_m3_Hwi_Module__state__V: LOAD > 0x20000144
    .data:xdc_runtime_Error_Module__state__V: LOAD > 0x20000204
    .data:ti_sysbios_family_arm_cc26xx_Timer_Module__state__V: LOAD > 0x200001e4
}

/* Content from ti.sysbios.xdcruntime (null): */

/* Content from ti.sysbios.utils (null): */

/* Content from configPkg (null): */

/* Content from xdc.services.io (null): */



/*
 * symbolic aliases for static instance objects
 */
xdc_runtime_Startup__EXECFXN__C = 1;
xdc_runtime_Startup__RESETFXN__C = 1;
xdc_rov_runtime_Mon__checksum = 1;
xdc_rov_runtime_Mon__write = 1;


SECTIONS
{
    .bootVecs:  type = DSECT
    .resetVecs: load > 0x0
    .vecs: load > 0x20000000, type = NOLOAD



    xdc.meta: type = COPY
    xdc.noload: type = COPY
}
