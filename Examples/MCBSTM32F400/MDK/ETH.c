
#include "cmsis_compiler.h"
#include "Driver_ETH_MAC.h"

extern ARM_DRIVER_ETH_MAC Driver_ETH_MAC0;

static ARM_DRIVER_VERSION GetVersion (void) {
  return Driver_ETH_MAC0.GetVersion();
}

static ARM_ETH_MAC_CAPABILITIES GetCapabilities (void) {
  return Driver_ETH_MAC0.GetCapabilities();
}

static int32_t Initialize (ARM_ETH_MAC_SignalEvent_t cb_event) {
  return Driver_ETH_MAC0.Initialize(cb_event);
}

static int32_t Uninitialize (void) {
  return Driver_ETH_MAC0.Uninitialize();
}

int32_t ETH1_PowerControl (ARM_POWER_STATE state) {
  return Driver_ETH_MAC0.PowerControl(state);
}

static int32_t SVC_PowerControl (ARM_POWER_STATE state) {
  register int32_t ret __ASM("r0");
  __ASM volatile ("svc 1" : "=r"(ret) : "r"(state) : "r1","r2","r3","r12","cc");
  return (int32_t) ret;
}

static int32_t GetMacAddress (ARM_ETH_MAC_ADDR *ptr_addr) {
  return Driver_ETH_MAC0.GetMacAddress(ptr_addr);
}

static int32_t SetMacAddress (const ARM_ETH_MAC_ADDR *ptr_addr) {
  return Driver_ETH_MAC0.SetMacAddress(ptr_addr);
}

static int32_t SetAddressFilter (const ARM_ETH_MAC_ADDR *ptr_addr, uint32_t num_addr) {
  return Driver_ETH_MAC0.SetAddressFilter(ptr_addr, num_addr);
}

static int32_t SendFrame (const uint8_t *frame, uint32_t len, uint32_t flags) {
  return Driver_ETH_MAC0.SendFrame(frame, len, flags);
}

static int32_t ReadFrame (uint8_t *frame, uint32_t len) {
  return Driver_ETH_MAC0.ReadFrame(frame, len);
}

static uint32_t GetRxFrameSize (void) {
  return Driver_ETH_MAC0.GetRxFrameSize();
}

static int32_t GetRxFrameTime (ARM_ETH_MAC_TIME *time) {
  return Driver_ETH_MAC0.GetRxFrameTime(time);
}

static int32_t GetTxFrameTime (ARM_ETH_MAC_TIME *time) {
  return Driver_ETH_MAC0.GetTxFrameTime(time);
}

static int32_t ControlTimer (uint32_t control, ARM_ETH_MAC_TIME *time) {
  return Driver_ETH_MAC0.ControlTimer(control, time);
}

static int32_t Control (uint32_t control, uint32_t arg) {
  return Driver_ETH_MAC0.Control(control, arg);
}

static int32_t PHY_Read (uint8_t phy_addr, uint8_t reg_addr, uint16_t *data) {
  return Driver_ETH_MAC0.PHY_Read(phy_addr, reg_addr, data);
}

static int32_t PHY_Write (uint8_t phy_addr, uint8_t reg_addr, uint16_t data) {
  return Driver_ETH_MAC0.PHY_Write(phy_addr, reg_addr, data);
}

ARM_DRIVER_ETH_MAC Driver_ETH_MAC1 = {
  GetVersion,
  GetCapabilities,
  Initialize,
  Uninitialize,
  SVC_PowerControl,
  GetMacAddress,
  SetMacAddress,
  SetAddressFilter,
  SendFrame,
  ReadFrame,
  GetRxFrameSize,
  GetRxFrameTime,
  GetTxFrameTime,
  ControlTimer,
  Control,
  PHY_Read,
  PHY_Write
};
