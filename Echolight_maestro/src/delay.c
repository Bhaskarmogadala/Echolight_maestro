void delay_US(unsigned int delay_us)
{
	delay_us*=12;
	while(delay_us--);
}
void delay_MS(unsigned int delay_ms)
{
	delay_ms*=12000;
	while(delay_ms--);
}
void delay_S(unsigned int delay_s)
{
	delay_s*=12000000;
	while(delay_s--);
}
