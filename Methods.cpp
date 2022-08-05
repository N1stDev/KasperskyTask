#include "Storage.h"
#include<mutex>

mutex mtx;

void Storage::add_product(string vend, string manuf, string name, int pr) {
	unique_lock<mutex> ul2(mtx);
	products[vend] = Product(vend, name, manuf, pr);
	manufacturers.emplace(manuf, Product(vend, name, manuf, pr));
}

void Storage::remove_product(string vend) {
	unique_lock<mutex> ul2(mtx);
	if (products.size() > 0) {
		products.erase(products.find(vend));
	}
}

void Storage::get_product(string vend) {
	unique_lock<mutex> ul(mtx);
	if (products.count(vend) == 0) {
		cout << "������ � ��������� " << vend << " ��� � �������!" << endl;
	}
	else {
		cout << "����� � ��������� " << vend << " ������!" << endl;
		cout << "������������: " << products[vend].product_name << endl;
		cout << "�������������: " << products[vend].manufacturer << endl;
		cout << "����: " << products[vend].price << endl;
	}
	cout << endl;
}

void Storage::get_manufacturer_products(string manuf) {
	unique_lock<mutex> ul(mtx);
	cout << "������ �� ������������� " << manuf << ":" << endl;
	auto range = manufacturers.equal_range(manuf);
	for (auto it = range.first; it != range.second; ++it) {
		if (products.count(it->second.vendor_code)) {
			cout << "�������: " << it->second.vendor_code << endl;
			cout << "������������: " << it->second.product_name << endl;
			cout << "����: " << it->second.price << endl;
			cout << endl;
		}
	}
	cout << endl;
}

void Storage::print_info() {
	unique_lock<mutex> ul(mtx);
	cout << "�������� �������: " << endl;
	for (auto it = products.begin(); it != products.end(); ++it) {
		cout << "�������: " << it->first << endl;
		cout << "������������ " << it->second.product_name << endl;
		cout << "�������������: " << it->second.manufacturer << endl;
		cout << "����: " << it->second.price << endl;
		cout << endl;
	}
	cout << endl;
}