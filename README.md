C言語在庫管理システム（中日対応）

## ✅ システム概要

本システムは、C言語で実装された簡易在庫管理システムです。  
主に以下の機能を提供し、小規模業務や学習用途に適しています。

- 商品の追加  
- 商品の削除  
- 商品情報の更新  
- 商品情報の検索  
- 商品一覧の表示  
- システム終了  

## ✅ 設計概要

### 1. 要件分析
基本的な在庫管理操作をCLI（コマンドライン）ベースで行います。

---

### 2. データ構造設計

- `struct Product`：商品情報を保持する構造体  
  - `int id`：商品ID（ユニーク）  
  - `char name[50]`：商品名  
  - `int quantity`：在庫数  
  - `float price`：単価  

- 商品は `products[100]` に格納し、最大100件に対応  
- `int productCount` で現在の件数を管理  

---

### 3. 機能モジュール

| 関数名              | 説明                          |
|------------------|------------------------------|
| `addProduct()`    | 商品の新規追加                |
| `deleteProduct()` | 商品の削除                    |
| `updateProduct()` | 商品情報の更新                |
| `searchProduct()` | 商品をIDで検索し表示          |
| `displayProducts()`| 登録済み全商品の一覧を表示   |
| `main()`          | メニュー操作ループの実装     |

---

## ✅ 各機能の説明

### 📌 商品追加（`addProduct`）
- 登録件数が上限未満であることを確認  
- ユーザーからID・名前・数量・単価を入力し、配列に追加

### 📌 商品削除（`deleteProduct`）
- 指定IDの商品を検索  
- 見つかった場合、後ろの要素を詰めて削除処理を行う

### 📌 商品更新（`updateProduct`）
- 商品IDで検索し、新しいデータ（名前・数量・単価）を入力して上書き

### 📌 商品検索（`searchProduct`）
- 指定IDの商品を検索し、該当情報を表示

### 📌 商品一覧（`displayProducts`）
- 登録済みの全商品を表形式で出力  
- 件数が0件なら「在庫は空です」と表示

### 📌 メニュー表示・操作
- ユーザー選択に応じて各機能を呼び出すループを実装

---

## ✅ 使用技術

- C言語（構造体、配列、標準入出力）  
- ファイル操作・動的メモリは未使用

---

## ✅ 学習効果

- 構造体と配列の組み合わせによるCRUD実装  
- 基本的なアルゴリズム操作（線形探索、要素の挿入・削除）

---

## ✅ 発展課題（応用編）

- ファイル保存（データの永続化）  
- 動的メモリ管理（mallocによる柔軟な配列拡張）  
- 構造体のポインタ操作  
- リンクリストによるメモリ効率改善

---

## ✅ 動作確認環境

- GCCコンパイラ（Linux / Windows）  
- CLI上での操作を前提としています

---

📝 **このREADMEは学習用のCプロジェクトに最適化されています。商用利用の場合は、エラー処理、入力バリデーション、安全なメモリ管理の追加を推奨します。**
