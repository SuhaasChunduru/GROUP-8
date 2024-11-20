#include <iostream>
#include <string>
class Car {
public:
   std::string brand;
   std::string model;
   double dailyRate;
   int quantity;
   Car(const std::string& brand = "", const std::string& model = "",
  double dailyRate = 0.0, int quantity = 0)  : brand(brand), model(model),    dailyRate(dailyRate), quantity(quantity) {}
};
class CarRentalSystem {
private:
   static const int carCount = 27;
   Car cars[carCount];
public:
   CarRentalSystem() {
       initializeCars();
   }
   void initializeCars() {
       std::string brands[] ={"Toyota", "Honda", "Ford", "Suzuki", "Mahindra", "Tata", "Volvo", "Volkswagen", "MG"};
       std::string models[][3] = {
           {"Camry", "Corolla", "Rav4"},
           {"Accord", "Civic", "Pilot"},
           {"Mustang", "Fusion", "Explorer"},
           {"Swift", "Baleno", "Vitara"},
           {"Scorpio", "XUV500", "Thar"},
           {"Altroz", "Tiago", "Harrier"},
           {"XC90", "S60", "V60"},
           {"Golf", "Passat", "Tiguan"},
           {"Hector", "ZS EV", "Gloster"}
       };
       int index = 0;
       for (int i = 0; i < 9; ++i) {
           for (int j = 0; j < 3; ++j) {
               cars[index] = Car(brands[i], models[i][j], 30.0 + i * 5.0, 5);
               index++;
           }
       }
   }
   void displayAvailableCarBrands() const {
       std::cout << "Available Car Brands:" << std::endl;
       std::string uniqueBrands[9];
       int uniqueBrandCount = 0;
       for (const Car& car : cars) {
           bool found = false;
           for (int i = 0; i < uniqueBrandCount; ++i) {
               if (uniqueBrands[i] == car.brand) {
                   found = true;
                   break;
               }
           }
           if (!found) {
               uniqueBrands[uniqueBrandCount++] = car.brand;
               std::cout << car.brand << std::endl;
           }
       }
       std::cout << std::endl;
   }
   bool isValidBrand(const std::string& brand) const {
       for (const Car& car : cars) {
           if (car.brand == brand) {
               return true;
           }
       }
       return false;
   }
   void displayAvailableModelsForBrand(const std::string& brand) const {
       std::cout << "Available Models for " << brand << ":" << std::endl;
       for (const Car& car : cars) {
           if (car.brand == brand) {
               std::cout << car.model << std::endl;
           }
       }
       std::cout << std::endl;
   }
   void displayAvailableCars() const {
       std::cout << "Available Cars:" << std::endl;
       for (const Car& car : cars) {
           std::cout << car.brand << " " << car.model << " - ₹" << car.dailyRate <<" per day | Available: " << car.quantity << std::endl;
       }
       std::cout << std::endl;
   }
   double rentCar(const std::string& brand, const std::string& model, int days) {
       for (Car& car : cars) {
           if (car.brand == brand && car.model == model && car.quantity > 0) {
               double totalRent = car.dailyRate * days;
               std::cout << "Cost per day for " << car.brand << " " << car.model << ": ₹" << car.dailyRate << std::endl;
               std::cout << "You have rented a " << car.brand << " " << car.model << " for " << days << " days." << std::endl;
               std::cout << "Total Rent: ₹" << totalRent << std::endl;
 
               car.quantity--; // Reduce the available quantity
 
               return totalRent;
           }
       }
       std::cout << "Car not available for rent or out of stock." << std::endl;
       return 0.0;
   }
   void returnCar(const std::string& brand, const std::string& model) {
       for (Car& car : cars) {
           if (car.brand == brand && car.model == model) {
               std::cout << "You have returned a " << car.brand << " " << car.model << "." << std::endl;
 
               car.quantity++; // Increase the available quantity
               return;
           }
       }
       std::cout << "Invalid return. Car not found or already returned." << std::endl;
   }
};
int main() {
   CarRentalSystem rentalSystem;
   std::cout << "Welcome to Creative Car Rentals!" << std::endl;
   rentalSystem.displayAvailableCarBrands();
   std::string chosenBrand, chosenModel;
   int rentalDays;
   std::cout << "Enter the brand of the car you want to rent: ";
   std::cin >> chosenBrand;
   if (!rentalSystem.isValidBrand(chosenBrand)) {
       std::cout << "Invalid brand. Please choose from the available brands." << std::endl;
       return 1;
   }
   rentalSystem.displayAvailableModelsForBrand(chosenBrand);
   std::cout << "Enter the model of the car you want to rent: ";
   std::cin >> chosenModel;
   std::cout << "Enter the number of days you want to rent the car (max 7 days): ";
   std::cin >> rentalDays;
   if (rentalDays <= 0 || rentalDays > 7) {
       std::cout << "Invalid number of days. Please enter a number between 1 and 7." << std::endl;
       return 1;
   }
   double totalRent = rentalSystem.rentCar(chosenBrand, chosenModel, rentalDays);
   std::cout << "Thank you for choosing Creative Car Rentals!" << std::endl;
   std::cout << "Your total rent is: ₹" << totalRent << std::endl;
   return 0;
}