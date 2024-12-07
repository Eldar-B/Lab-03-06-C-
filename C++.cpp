#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class PricingPolicy {
private:
    string update = "last price update 25.11.2024";
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

class FieldCharacteristics {
private:
    static int totalFields; // Статическое поле
    float field_cost = 0, size = 0;

    float time_plowing = 0, cost_plowing = 0;
    float time_cultivation = 0, cost_cultivation = 0;
    float time_rolling = 0, cost_rolling = 0;
    float cost_fertilization = 0, time_fertilization = 0, volume_mineral_fertilizers = 0;

    float final_time = 0, final_cost = 0;

public:
    FieldCharacteristics(float size, const PricingPolicy& pp) : size(size) {
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

        ++totalFields; // Увеличиваем количество полей
    }

    ~FieldCharacteristics() {
        --totalFields; // Уменьшаем количество полей
    }

    static int getTotalFields() {
        return totalFields;
    }

    float* getFinalCostPointer() {
        return &final_cost;
    }

    float& getFinalCostReference() {
        return final_cost;
    }

    bool compareCost(const FieldCharacteristics& other) const {
        return this->final_cost > other.final_cost;
    }

    void display() const {
        cout << "Field size: " << size << " He" << endl;
        cout << "Field cost: " << field_cost << " rub" << endl;
        cout << "=======================================" << endl;
        cout << "Plowing time: " << time_plowing << " h" << endl;
        cout << "Cultivation time: " << time_cultivation << " h" << endl;
        cout << "Rolling time: " << time_rolling << " h" << endl;
        cout << "Fertilization time: " << time_fertilization << " h" << endl;
        cout << "Final time: " << final_time << " h" << endl;
        cout << "=======================================" << endl;
        cout << "Plowing cost: " << cost_plowing << " rub" << endl;
        cout << "Cultivation cost: " << cost_cultivation << " rub" << endl;
        cout << "Rolling cost: " << cost_rolling << " rub" << endl;
        cout << "Fertilization cost: " << cost_fertilization << " rub" << endl;
        cout << "Final cost: " << final_cost << " rub" << endl;
        cout << "=======================================" << endl;
        cout << "Additional (volume of mineral fertilizers): " << volume_mineral_fertilizers << " L" << endl;
    }

    FieldCharacteristics operator+(const FieldCharacteristics& other) const {
        return FieldCharacteristics(this->size + other.size, PricingPolicy());
    }

    FieldCharacteristics& operator++() {
        ++size;
        return *this;
    }

    FieldCharacteristics operator++(int) {
        FieldCharacteristics temp = *this;
        ++size;
        return temp;
    }

    friend bool compareFieldSizes(const FieldCharacteristics& f1, const FieldCharacteristics& f2) {
        return f1.size > f2.size;
    }
};

int FieldCharacteristics::totalFields = 0;

int main() {
    PricingPolicy pp;
    vector<unique_ptr<FieldCharacteristics>> fieldArray; // Массив динамических объектов
    int game_status = 0;
    do {
        cout << "=============================================" << endl;
        cout << "Add field | Show info | Total fields | Exit" << endl;
        cout << "    1     |     2     |      4       |   3" << endl;
        cout << "=============================================" << endl;

        cin >> game_status;

        if (game_status == 1) {
            float size;
            cout << "Enter field size in He: ";
            cin >> size;
            fieldArray.push_back(make_unique<FieldCharacteristics>(size, pp));
        }
        else if (game_status == 2) {
            for (size_t i = 0; i < fieldArray.size(); ++i) {
                cout << "Field " << i + 1 << " details:" << endl;
                fieldArray[i]->display();
            }
        }
        else if (game_status == 4) {
            cout << "Total fields: " << FieldCharacteristics::getTotalFields() << endl;
        }
    } while (game_status != 3);

    return 0;
}