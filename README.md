# スライサーの作成
多軸に対応したマルチ平面スライサを作成する

## 開発環境
Mac

## 各ディレクトリについて
+ Slicer : 最初期のプログラム, 基本的にいじってない、レガシー
+ slicer_2D : 2D用? 
+ Slicer_v2 : 通常のプリントならここですでに完成している,Gコードの出力まで対応
+ Slicer_v2_arc : 曲線スライサ 
+ Test_Clipper : Clipperをつかって色々やるディレクトリ

## Qt5の環境
5.14.2  
[Qtホームページからインストーラを入れる](https://www.qt.io/download?hsCtaTracking=f24f249b-61fb-4dec-9869-50512342f8d9%7Cf3adf380-4740-4f7e-9e49-d06fa99445fa)


## TODO
- [ ] ASCII形式のSTLファイルへの対応
- [x] スライスの実装
- [x] Buildの対応(CMakeの修正)
- [ ] 通常スライサと曲線スライサのクラス化
- [ ] 通常スライサと曲線スライサの統合
- [ ] Zig-Zagアルゴリズムの実装