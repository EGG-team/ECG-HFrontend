void FALLING_interrupt_ECG_p();
void RISING_interrupt_ECG_p();
void FALLING_interrupt_ECG_n();
void RISING_interrupt_ECG_n();

class ECG
{
	static unsigned int raw[250];
	static float time_ms;
	static int  A_pin;
	static int  LOp_pin;
	static int  LOn_pin;
	static bool ecg_active_p;
	static bool ecg_active_n;
public:

	ECG(float _time_ms, int _A_pin, int _LOp_pin, int _LOn_pin)
	{
		noInterrupts();

		time_ms = time_ms;
		A_pin   = _A_pin; 
		LOp_pin = _LOp_pin; 
		LOn_pin = _LOn_pin;
		ecg_active_p = false;
		ecg_active_n = false;

		pinMode(LOp_pin, INPUT);
		pinMode(LOn_pin, INPUT);

		attachInterrupt(LOp_pin, &FALLING_interrupt_ECG_p, FALLING);
		attachInterrupt(LOn_pin, &FALLING_interrupt_ECG_n, FALLING);

		interrupts();
	}

	~ECG()
	{

	}

	friend void FALLING_interrupt_ECG_p();
	friend void RISING_interrupt_ECG_p();
	friend void FALLING_interrupt_ECG_n();
	friend void RISING_interrupt_ECG_n();

};

void FALLING_interrupt_ECG_p()
{
	ECG::ecg_active_p = true;
	attachInterrupt(ECG::LOp_pin, &RISING_interrupt_ECG_p, RISING);

	while(){}
}

void RISING_interrupt_ECG_p()
{
	ECG::ecg_active_p = false;
	attachInterrupt(ECG::LOp_pin, &FALLING_interrupt_ECG_p, FALLING);
}

void FALLING_interrupt_ECG_n()
{
	ECG::ecg_active_n = true;
	attachInterrupt(ECG::LOn_pin, &RISING_interrupt_ECG_n, RISING);
}

void RISING_interrupt_ECG_n()
{
	ECG::ecg_active_n = false;
	attachInterrupt(ECG::LOn_pin, &FALLING_interrupt_ECG_n, FALLING);
}
	
