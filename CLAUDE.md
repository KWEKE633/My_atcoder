# CLAUDE.md

AtCoder 用の個人作業スペース。Claude Code では主に **自作ライブラリの作成・補強** を行う。

## ディレクトリ構成

| パス | 内容 |
| --- | --- |
| `main.cpp` | コンテスト用テンプレート兼 自作ライブラリ本体（`// -----自作ライブラリ (随時追加予定)-----` 以降に struct を追加していく） |
| `memo.cpp` | アルゴリズムの断片メモ（LPS, LIS など。コメントアウト状態で保存） |
| `templete/` | テンプレート素材（`All.hpp` は標準ヘッダ一括 include） |
| `practice/` | 練習用（独自の `Makefile` と `main.cpp`） |
| `AHC/` | AtCoder Heuristic Contest 用 |
| `atcoder/` | AtCoder Library (ACL)。**外部ライブラリなので編集しない**。`.gitignore` 対象 |

## ビルド・実行

```bash
make          # main.cpp -> a.out  (-Wall -Wextra -Werror -std=c++20 -I .)
./a.out < in.txt
make fclean   # *.o と a.out を削除
```

- `-Werror` なので警告が 1 つでも出るとビルド失敗する。未使用変数は `(void)x;` で潰す（`main` 内の `(void)INF;` と同じ流儀）。
- `-I .` により `#include <atcoder/xxx>` はリポジトリ直下の `atcoder/` を参照する。新しい環境では ACL を `atcoder/` に配置してからビルドすること。

## ライブラリを書くときの方針

- 既存のコードスタイルに合わせる: `rep`/`repp`/`ll`/`vec`/`vvec`/`chmin`/`chmax` などのマクロ・エイリアスを使ってよい。
- 1 つの機能は 1 つの `struct`（必要なら `template`）にまとめ、`main.cpp` の自作ライブラリ欄にコピペで使える形にする。
- 先頭に `// -名前-  概要` 形式のコメントを付け、計算量と使い方（コンストラクタ・主要メソッド）を簡潔に書く。
- 0-indexed / 半開区間 `[l, r)` を基本とし、違う場合はコメントに明記する。
- ACL に同等機能がある場合は、その違い（自作版の利点）をコメントで示す。
- 追加・修正したら、小さなテストケースで `make` → 実行して動作確認する。

## Git 運用

- `main` から作業ブランチを切って作業する。
- **`git add` / `commit` / `push` などの git 操作はユーザーの明示的な指示があるまで行わない。**
- 依頼と関係ないファイルは変更しない。
