void setup()
{
	Serial.begin(115200);
	Serial.setTimeout(1);
}

void loop()
{
	float a = 3.14;
	float b = 2.5;
	float c = 55.55;

	Serial.println(a);
	Serial.println(b);
	Serial.println(c);
}
