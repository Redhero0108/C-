#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <wchar.h>

#define MAX_PRODUCTS 100  // 最大库存容量

// 商品结构体
typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Product;

Product products[MAX_PRODUCTS]; // 商品数组
int productCount = 0; // 当前商品数量

// 添加商品
void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("库存已满，无法添加新商品！\n");
        return;
    }

    Product p;
    printf("输入商品ID: ");
    scanf("%d", &p.id);
    printf("输入商品名称: ");
    scanf("%s", p.name);
    printf("输入商品数量: ");
    scanf("%d", &p.quantity);
    printf("输入商品价格: ");
    scanf("%f", &p.price);

    products[productCount++] = p;
    printf("商品添加成功！\n");
}

// 删除商品
void deleteProduct() {
    int id, i, found = 0;
    printf("输入要删除的商品ID: ");
    scanf("%d", &id);

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = 1;
            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }
            productCount--;
            printf("商品删除成功！\n");
            break;
        }
    }
    if (!found) {
        printf("未找到商品ID %d\n", id);
    }
}

// 更新商品信息
void updateProduct() {
    int id, i, found = 0;
    printf("输入要更新的商品ID: ");
    scanf("%d", &id);

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = 1;
            printf("输入新商品名称: ");
            scanf("%s", products[i].name);
            printf("输入新商品数量: ");
            scanf("%d", &products[i].quantity);
            printf("输入新商品价格: ");
            scanf("%f", &products[i].price);
            printf("商品信息更新成功！\n");
            break;
        }
    }
    if (!found) {
        printf("未找到商品ID %d\n", id);
    }
}

// 查询商品信息
void searchProduct() {
    int id, i, found = 0;
    printf("输入要查询的商品ID: ");
    scanf("%d", &id);

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = 1;
            printf("商品ID: %d\n", products[i].id);
            printf("商品名称: %s\n", products[i].name);
            printf("商品数量: %d\n", products[i].quantity);
            printf("商品价格: %.2f\n", products[i].price);
            break;
        }
    }
    if (!found) {
        printf("未找到商品ID %d\n", id);
    }
}

// 显示所有商品
void displayProducts() {
    if (productCount == 0) {
        printf("库存为空！\n");
        return;
    }

    printf("\n当前库存商品列表：\n");
    printf("ID\t名称\t数量\t价格\n");
    printf("---------------------------------\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d\t%s\t%d\t%.2f\n", products[i].id, products[i].name, products[i].quantity, products[i].price);
    }
}

// 进货（增加库存）
void stockIn() {
    int id, qty, i, found = 0;
    printf("输入进货的商品ID: ");
    scanf("%d", &id);
    printf("输入进货数量: ");
    scanf("%d", &qty);

    if (qty <= 0) {
        printf("进货数量必须大于 0！\n");
        return;
    }

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = 1;
            products[i].quantity += qty;
            printf("进货成功！商品 %s 的库存增加 %d，总库存为 %d\n", products[i].name, qty, products[i].quantity);
            break;
        }
    }
    if (!found) {
        printf("未找到商品ID %d\n", id);
    }
}

// 出货（减少库存）
void stockOut() {
    int id, qty, i, found = 0;
    printf("输入出货的商品ID: ");
    scanf("%d", &id);
    printf("输入出货数量: ");
    scanf("%d", &qty);

    if (qty <= 0) {
        printf("出货数量必须大于 0！\n");
        return;
    }

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = 1;
            if (products[i].quantity >= qty) {
                products[i].quantity -= qty;
                printf("出货成功！商品 %s 的库存减少 %d，剩余库存为 %d\n", products[i].name, qty, products[i].quantity);
            } else {
                printf("库存不足！当前库存仅有 %d 件。\n", products[i].quantity);
            }
            break;
        }
    }
    if (!found) {
        printf("未找到商品ID %d\n", id);
    }
}
void saveToFile() {
    FILE *file = fopen("inventory.txt", "w");
    if (!file) {
        printf("无法打开文件进行写入！\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%d %s %d %.2f\n", products[i].id, products[i].name, products[i].quantity, products[i].price);
    }
    fclose(file);
    printf("数据已保存！\n");
}
void loadFromFile() {
    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf("未找到数据文件，可能是第一次运行。\n");
        return;
    }

    productCount = 0;
    while (fscanf(file, "%d %s %d %f", &products[productCount].id, products[productCount].name, 
                  &products[productCount].quantity, &products[productCount].price) != EOF) {
        productCount++;
    }
    fclose(file);
    printf("数据加载成功，共加载 %d 个商品。\n", productCount);
}
void calculateTotalValue() {
    float totalValue = 0;
    for (int i = 0; i < productCount; i++) {
        totalValue += products[i].quantity * products[i].price;
    }
    printf("当前库存总价值: %.2f 元\n", totalValue);
}

// 主菜单
void menu() {
    int choice;
    while (1) {
        printf("\n===== 库存管理系统 =====\n");
        printf("1. 添加商品\n");
        printf("2. 删除商品\n");
        printf("3. 更新商品信息\n");
        printf("4. 查询商品信息\n");
        printf("5. 显示所有商品\n");
        printf("6. 进货（增加库存）\n");
        printf("7. 出货（减少库存）\n");
        printf("8. 统计库存总价值\n");
		printf("9. 退出系统\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addProduct(); saveToFile();break;
            case 2: deleteProduct(); saveToFile();break;
            case 3: updateProduct(); saveToFile();break;
            case 4: searchProduct(); break;
            case 5: displayProducts(); break;
            case 6: stockIn();saveToFile(); break;
            case 7: stockOut(); saveToFile();break;
            case 8: calculateTotalValue();break;
			case 9:printf("退出系统...\n"); exit(0);
            default: printf("无效选项，请重新输入。\n");
        }
    }
}

int main() {

    SetConsoleCP(65001);        // 设置输入编码为 UTF-8
    SetConsoleOutputCP(65001);  // 设置输出编码为 UTF-8
    loadFromFile();  // 启动时加载数据
    menu();
    return 0;
}

