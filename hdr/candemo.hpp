
#ifndef candemo_hpp
#define candemo_hpp


extern int demo_can_sent(int can_id, int can_dlc, const char* can_data);
extern int demo_can_recv(void);
extern int demo_can_filter(int argc, char **argv);

#endif /* candemo_hpp */