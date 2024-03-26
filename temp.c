// main.cpp (Function Execution / Calls)

// functions.h (Where you have all the function headers, ie. void NEOM8N_Receive_Uart(uint8_t *data, uint16_t size))
// function.c (Where you implement the functions)

void calcVel(double dis, double time);

void calcVel(double dis, double time)
{
    return dis / time;
}

int main()
{
    calcVel(10, 2);
    return 0;
}

// integer = 2.1B 32 Bytes
// float = 2.1F
// double = 2.1

make all 