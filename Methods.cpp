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
		cout << "Product with vendor code " << vend << " not found!" << endl;
	}
	else {
		cout << "Product with vendor code " << vend << " found!" << endl;
		cout << "Name: " << products[vend].product_name << endl;
		cout << "Manufacturer: " << products[vend].manufacturer << endl;
		cout << "Price: " << products[vend].price << endl;
	}
	cout << endl;
}

void Storage::get_manufacturer_products(string manuf) {
	unique_lock<mutex> ul(mtx);
	cout << "Products of " << manuf << ":" << endl;
	auto range = manufacturers.equal_range(manuf);
	for (auto it = range.first; it != range.second; ++it) {
		if (products.count(it->second.vendor_code)) {
			cout << "Vendor code: " << it->second.vendor_code << endl;
			cout << "Name: " << it->second.product_name << endl;
			cout << "Price: " << it->second.price << endl;
			cout << endl;
		}
	}
	cout << endl;
}

void Storage::print_info() {
	unique_lock<mutex> ul(mtx);
	cout << "Products: " << endl;
	for (auto it = products.begin(); it != products.end(); ++it) {
		cout << "Vendor code: " << it->first << endl;
		cout << "Name: " << it->second.product_name << endl;
		cout << "Manufacturer: " << it->second.manufacturer << endl;
		cout << "Price: " << it->second.price << endl;
		cout << endl;
	}
	cout << endl;
}