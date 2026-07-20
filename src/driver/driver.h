#pragma once

// Binary driver data embedded in executable
unsigned char driver_bytes[] = { 0x4D, 0x5A, 0x90, 0x00, 0x03, 0x00, 0x00, 0x00 };
unsigned int driver_size = 6912;

// Driver control codes and definitions
#define DRIVER_IOCTL_BASE 0x22A000
#define IOCTL_SPOOF_HWID CTL_CODE(FILE_DEVICE_UNKNOWN, DRIVER_IOCTL_BASE, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_RECOVER_HWID CTL_CODE(FILE_DEVICE_UNKNOWN, DRIVER_IOCTL_BASE + 1, METHOD_BUFFERED, FILE_ANY_ACCESS)
