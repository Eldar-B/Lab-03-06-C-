#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Абстрактный базовый класс
class FieldBase {
protected:
    float size; // Защищенный член

public:
    FieldBase(float size) {
        if (size <= 0) {
            throw invalid_argument("Field size must be greater than 0.");
        }
        this->size = size;
    }
    virtual ~FieldBase() {}

    // Геттер для size
    float getSize() const { return size; }

    virtual void display(ostream& os) const = 0; // Абстрактный метод
    virtual float getFinalCost() const = 0;

    friend ostream& operator<<(ostream& os, const FieldBase& field) {
        field.display(os);
        return os;
    }
};

// Класс политики ценообразования
class PricingPolicy {
private:
    string update = "last price update 25.11.2024";

protected:
    float field_cost = 500000;

    float time_plowing = 5, cost_plowing = 13000;
    float time_cultivation = 3, cost_cultivation = 11500;
    float time_rolling = 2, cost_rolling = 10000;
    float cost_fertilization = 11500, time_fertilization = 1, volume_mineral_fertilizers = 100;

public:
    PricingPolicy() {}

    float getFieldCost() const { return field_cost; }
    float getTimePlowing() const { return time_plowing; }
    float getCostPlowing() const { return cost_plowing; }
    float getTimeCultivation() const { return time_cultivation; }
    float getCostCultivation() const { return cost_cultivation; }
    float getTimeRolling() const { return time_rolling; }
    float getCostRolling() const { return cost_rolling; }
    float getTimeFertilization() const { return time_fertilization; }
    float getCostFertilization() const { return cost_fertilization; }
    float getVolumeMineralFertilizers() const { return volume_mineral_fertilizers; }

    float getFinalTime() const {
        return time_plowing + time_cultivation + time_rolling + time_fertilization;
    }
    float getFinalCost() const {
        return cost_plowing + cost_cultivation + cost_rolling + cost_fertilization;
    }

    string getUpdate() const { return update; }
};

// Класс характеристик поля
class FieldCharacteristics : public FieldBase {
protected:
    float field_cost = 0;

    float time_plowing = 0, cost_plowing = 0;
    float time_cultivation = 0, cost_cultivation = 0;
    float time_rolling = 0, cost_rolling = 0;
    float cost_fertilization = 0, time_fertilization = 0, volume_mineral_fertilizers = 0;

    float final_time = 0, final_cost = 0;

public:
    FieldCharacteristics(float size, const PricingPolicy& pp)
        : FieldBase(size) { // Вызов конструктора базового класса
        field_cost = pp.getFieldCost() * size;

        time_plowing = pp.getTimePlowing() * size;
        cost_plowing = pp.getCostPlowing() * size;

        time_cultivation = pp.getTimeCultivation() * size;
        cost_cultivation = pp.getCostCultivation() * size;

        time_rolling = pp.getTimeRolling() * size;
        cost_rolling = pp.getCostRolling() * size;

        cost_fertilization = pp.getCostFertilization() * size;
        time_fertilization = pp.getTimeFertilization() * size;
        volume_mineral_fertilizers = pp.getVolumeMineralFertilizers() * size;

        final_time = pp.getFinalTime() * size;
        final_cost = pp.getFinalCost() * size;
    }

    virtual void display(ostream& os) const override { // Виртуальная функция
        os << "Field size: " << getSize() << " He\n"; // Используем геттер для size
        os << "Field cost: " << field_cost << " rub\n";
        os << "Final cost: " << final_cost << " rub\n";
    }

    float getFinalCost() const override {
        return final_cost;
    }

    FieldCharacteristics& operator=(const FieldBase& other) { // Перегрузка оператора присваивания
        if (this != &other) {
            this->size = other.getSize(); // Используем геттер для size
        }
        return *this;
    }
};

// Производный класс (например, для орошения)
class IrrigatedField : public FieldCharacteristics {
private:
    float irrigation_cost;

public:
    IrrigatedField(float size, const PricingPolicy& pp, float irrigation_cost)
        : FieldCharacteristics(size, pp), irrigation_cost(irrigation_cost) {
    }

    void display(ostream& os) const override { // Перегрузка метода display
        os << "[Irrigated Field]\n";
        FieldCharacteristics::display(os); // Вызов базового метода
        os << "Irrigation cost: " << irrigation_cost << " rub\n";
        os << "Total cost: " << (getFinalCost() + irrigation_cost) << " rub\n";
    }
};

// Демонстрация
int main() {
    PricingPolicy pp;

    // Создание объектов
    FieldCharacteristics field1(10, pp);
    IrrigatedField field2(15, pp, 50000);

    // Динамическое использование
    shared_ptr<FieldBase> baseField = make_shared<IrrigatedField>(20, pp, 75000);

    cout << field1 << endl;
    cout << field2 << endl;

    baseField->display(cout); // Вызов через указатель на базовый класс

    return 0;
}
