// set Mode_Sender or Mode_Reciver
#define Mode Mode_Receiver

#if Mode == Mode_Sender

#elif Mode == Mode_Receiver

#else
    #error you need select Mode in config.h
#endif