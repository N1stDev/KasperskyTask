#include"Storage.h"
#include<thread>

void func1(Storage& mystorage) {
	mystorage.add_product("12345", "Manuf1", "Name1", 100);
	mystorage.add_product("62783", "Manuf2", "Name2", 900);
	mystorage.get_product("12345");
	mystorage.print_info();
	mystorage.remove_product("12345");
	mystorage.add_product("128", "Manuf3", "Name3", 400);
}

void func2(Storage& mystorage) {
	mystorage.add_product("564", "Manuf3", "Name4", 350);
	mystorage.add_product("19", "Manuf4", "Name5", 10000);
	mystorage.get_product("19");
	mystorage.add_product("12811", "Manuf3", "Name6", 820);
	mystorage.remove_product("564");
	mystorage.get_manufacturer_products("Manuf3");
	mystorage.print_info();
}

int main() {

	setlocale(LC_ALL, "rus");

	Storage mystorage;
	
	thread t1(func1, ref(mystorage));
	thread t2(func2, ref(mystorage));

	t1.join();
	t2.join();

	mystorage.print_info();
	mystorage.get_product("0");
	mystorage.get_manufacturer_products("a");
	mystorage.get_manufacturer_products("Manuf3");
	
	return 0;
}