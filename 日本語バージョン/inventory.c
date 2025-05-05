#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
        printf("在庫が満杯のため、新しい商品を追加できません。！\n");
        return;
    }

    Product p;
    printf("商品IDを入力してください:");
    scanf("%d", &p.id);

    printf("商品名を入力してください:");
    scanf("%s", p.name);
    printf("商品数量を入力してください:");
    scanf("%d", &p.quantity);
    printf("商品価格を入力してください:");
    scanf("%f", &p.price);

    products[productCount++] = p;
    printf("商品が正常に追加されました。！\n");
}

// 删除商品
void deleteProduct() {
    int id, i, found = 0;
    printf("削除する商品IDを入力してください:");
    scanf("%d", &id);

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = 1;
            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }
            productCount--;
            printf("商品が正常に削除されました！\n");
            break;
        }
    }
    if (!found) {
        printf("商品IDが見つかりませんでした。 %d\n", id);
    }
}

// 更新商品信息
void updateProduct() {
    int id, i, found = 0;
    printf("更新する商品IDを入力してください:");
    scanf("%d", &id);

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = 1;
            printf("新しい商品名を入力してください:");
            scanf("%s", products[i].name);
            printf("新しい商品数量を入力してください:");
            scanf("%d", &products[i].quantity);
            printf("新しい商品価格を入力してください:");
            scanf("%f", &products[i].price);
            printf("商品情報が正常に更新されました！\n");
            break;
        }
    }
    if (!found) {
        printf("商品IDが見つかりませんでした。 %d\n", id);
    }
}

// 查询商品信息
void searchProduct() {
    int id, i, found = 0;
    printf("検索する商品IDを入力してください:");
    scanf("%d", &id);

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = 1;
            printf("商品ID: %d\n", products[i].id);
            printf("商品名: %s\n", products[i].name);
            printf("商品数量: %d\n", products[i].quantity);
            printf("商品価格: %.2f\n", products[i].price);
            break;
        }
    }
    if (!found) {
        printf("商品IDが見つかりませんでした。 %d\n", id);
    }
}

// 显示所有商品
void displayProducts() {
    if (productCount == 0) {
        printf("在庫が空です！\n");
        return;
    }

    printf("\n現在の在庫商品リスト：\n");
  /*   printf("ID\t名\t数量\t価格\n");
    printf("---------------------------------\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d\t%s\t\t%d\t%.2f\n", products[i].id, products[i].name, products[i].quantity, products[i].price);
    } */

    printf("=======================================================\n");
    printf("| %-5s | %-20s | %-6s | %-8s |%-8s |\n", "ID", "名", "数量", "価格","価値");
    printf("=======================================================\n");

    for (int i = 0; i < productCount; i++) {
        printf("| %-5d | %-20s | %-6d | %-8.2f |%-8.2f |\n",
               products[i].id, products[i].name, products[i].quantity, products[i].price,products[i].quantity*products[i].price);
    }
    printf("=======================================================\n");

	
	
}

// 进货（增加库存）
void stockIn() {
    int id, qty, i, found = 0;
    printf("仕入れる商品IDを入力してください:");
    scanf("%d", &id);
    printf("仕入れ数量を入力してください: ");
    scanf("%d", &qty);

    if (qty <= 0) {
        printf("仕入れ数量は0より大きい必要があります。！\n");
        return;
    }

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = 1;
            products[i].quantity += qty;
            printf("仕入れ成功！商品 %s の在庫が %d 増加し、総在庫は%d\n", products[i].name, qty, products[i].quantity);
            break;
        }
    }
    if (!found) {
        printf("商品IDが見つかりませんでした。 %d\n", id);
    }
}

// 出货（减少库存）
void stockOut() {
    int id, qty, i, found = 0;
    printf("出荷する商品IDを入力してください:");
    scanf("%d", &id);
    printf("出荷数量を入力してください: ");
    scanf("%d", &qty);

    if (qty <= 0) {
        printf("出荷数量は0より大きい必要があります。！\n");
        return;
    }

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = 1;
            if (products[i].quantity >= qty) {
                products[i].quantity -= qty;
                printf("出荷成功！商品 %s の在庫が %d 減少し、残りの在庫は%d\n", products[i].name, qty, products[i].quantity);
            } else {
                printf("在庫不足！現在の在庫は %d 件のみです。。\n", products[i].quantity);
            }
            break;
        }
    }
    if (!found) {
        printf("商品IDが見つかりませんでした。 %d\n", id);
    }
}
void saveToFile() {
    FILE *file = fopen("inventory.txt", "w");
    if (!file) {
        printf("ファイルを開いて書き込みできません！\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%d %s %d %.2f\n", products[i].id, products[i].name, products[i].quantity, products[i].price);
    }
    fclose(file);
    printf("データが保存されました！\n");
}
void loadFromFile() {
    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf("データファイルが見つかりませんでした。初回実行の可能性があります。\n");
        return;
    }

    productCount = 0;
    while (fscanf(file, "%d %s %d %f", &products[productCount].id, products[productCount].name, 
                  &products[productCount].quantity, &products[productCount].price) != EOF) {
        productCount++;
    }
    fclose(file);
    printf("データの読み込みに成功しました。合計 %d 件の商品をロードしました。。\n", productCount);
}
void calculateTotalValue() {
    float totalValue = 0;
    for (int i = 0; i < productCount; i++) {
        totalValue += products[i].quantity * products[i].price;
    }
    printf("現在の在庫の総価値: %.2f 円\n", totalValue);
}

// 主菜单
void menu() {
    int choice;
    while (1) {
         printf("\n===== 在庫管理システム =====\n");
    printf("1. 商品を追加\n");
    printf("2. 商品を削除\n");
    printf("3. 商品情報を更新\n");
    printf("4. 商品情報を検索\n");
    printf("5. すべての商品を表示\n");
    printf("6. 仕入れ（在庫を増やす）\n");
    printf("7. 出荷（在庫を減らす）\n");
    printf("8. 在庫総価値を計算\n");
    printf("9. システムを終了\n");
    printf("操作を選択してください: ");
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
		    case 9:printf("システムを終了します...\n");exit(0);
default:printf("無効な選択です。もう一度入力してください。\n");

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

