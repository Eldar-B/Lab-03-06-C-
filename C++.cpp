#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class PricingPolicy {
    // Оставляем существующий код без изменений.
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
    // Оставляем существующий код без изменений.
private:
    static int totalFields; // Статическое поле
    float field_cost = 0, size = 0;

    float time_plowing = 0, cost_plowing = 0;
    float time_cultivation = 0, cost_cultivation = 0;
    float time_rolling = 0, cost_rolling = 0;
    float cost_fertilization = 0, time_fertilization = 0, volume_mineral_fertilizers = 0;

    float final_time = 0, final_cost = 0;

public:
    FieldCharacteristics(float size, const PricingPolicy& pp) {
        if (size <= 0) {
            throw invalid_argument("Field size must be greater than 0.");
        }
        this->size = size;
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
};

int FieldCharacteristics::totalFields = 0;

int main() {
    PricingPolicy pp;
    vector<vector<unique_ptr<FieldCharacteristics>>> fieldGroups; // Двумерный массив
    int game_status = 0;

    do {
        cout << "=============================================" << endl;
        cout << "Add group | Add field | Show info | Exit" << endl;
        cout << "    1     |     2     |     3     |   4" << endl;
        cout << "=============================================" << endl;

        cin >> game_status;

        try {
            if (game_status == 1) {
                fieldGroups.push_back(vector<unique_ptr<FieldCharacteristics>>());
                cout << "New group of fields created." << endl;
            }
            else if (game_status == 2) {
                if (fieldGroups.empty()) {
                    cout << "No groups available. Create a group first." << endl;
                }
                else {
                    size_t groupIndex;
                    cout << "Select group index (1 - " << fieldGroups.size() << "): ";
                    cin >> groupIndex;
                    if (groupIndex < 1 || groupIndex > fieldGroups.size()) {
                        throw out_of_range("Invalid group index.");
                    }

                    float size;
                    cout << "Enter field size in He: ";
                    cin >> size;
                    fieldGroups[groupIndex - 1].push_back(make_unique<FieldCharacteristics>(size, pp));
                }
            }
            else if (game_status == 3) {
                if (fieldGroups.empty()) {
                    cout << "No groups available." << endl;
                }
                else {
                    for (size_t i = 0; i < fieldGroups.size(); ++i) {
                        cout << "Group " << i + 1 << ":" << endl;
                        for (size_t j = 0; j < fieldGroups[i].size(); ++j) {
                            cout << "  Field " << j + 1 << " details:" << endl;
                            fieldGroups[i][j]->display();
                        }
                    }
                }
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    } while (game_status != 4);

    return 0;
}