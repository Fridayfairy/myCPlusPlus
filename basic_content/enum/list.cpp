#include <iostream>
using namespace std;

typedef enum jy_type {
        JY_TYPE_FIRE = 0,       // 火
        JY_TYPE_SMOKE = 1,          // 烟
        JY_TYPE_NEST = 2,           // 鸟巢
        JY_TYPE_WIREDGARBAGE = 3,   // 导线异物
        JY_TYPE_VEHICLE = 4,        // 施工机械
        JY_TYPE_TOWERCRANE = 5,     // 塔吊
        JY_TYPE_TRUCKCRANE = 6,     // 吊车
        JY_TYPE_BULLDOZER = 7,      // 铲车
        JY_TYPE_PUMPTRUCK = 8,      // 水泥泵车
        JY_TYPE_TRUCK = 9,          // 车辆
        JY_TYPE_EXCAVATOR = 10,      // 挖掘机
        JY_TYPE_PILINGRIG = 11,      // 打桩机
        JY_TYPE_ROLLER = 12,         // 压路机
        JY_TYPE_FENCE = 13,          // 围挡
        JY_TYPE_WATERBARRIER = 14,   // 水马
        JY_TYPE_HELMET = 15,         // 安全帽
        JY_TYPE_MISSINGCOVER = 16,   // 井盖缺失
} jy_type_e;

#define JY_TYPE_COUNT (JY_TYPE_MISSINGCOVER + 1)

int main() {
  cout << JY_TYPE_COUNT << endl;
  return 0;
}