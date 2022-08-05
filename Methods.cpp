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
		cout << "Товара с артикулом " << vend << " нет в наличии!" << endl;
	}
	else {
		cout << "Товар с артикулом " << vend << " найден!" << endl;
		cout << "Наименование: " << products[vend].product_name << endl;
		cout << "Производитель: " << products[vend].manufacturer << endl;
		cout << "Цена: " << products[vend].price << endl;
	}
	cout << endl;
}

void Storage::get_manufacturer_products(string manuf) {
	unique_lock<mutex> ul(mtx);
	cout << "Товары от производителя " << manuf << ":" << endl;
	auto range = manufacturers.equal_range(manuf);
	for (auto it = range.first; it != range.second; ++it) {
		if (products.count(it->second.vendor_code)) {
			cout << "Артикул: " << it->second.vendor_code << endl;
			cout << "Наименование: " << it->second.product_name << endl;
			cout << "Цена: " << it->second.price << endl;
			cout << endl;
		}
	}
	cout << endl;
}

void Storage::print_info() {
	unique_lock<mutex> ul(mtx);
	cout << "Перечень товаров: " << endl;
	for (auto it = products.begin(); it != products.end(); ++it) {
		cout << "Артикул: " << it->first << endl;
		cout << "Наименование " << it->second.product_name << endl;
		cout << "Производитель: " << it->second.manufacturer << endl;
		cout << "Цена: " << it->second.price << endl;
		cout << endl;
	}
	cout << endl;
}