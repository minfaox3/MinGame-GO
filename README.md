# Painter
Qt4のときに作成した囲碁アプリの途中（石を置いたりするところまで）のものです。
![thumb](https://github.com/minfaox3/MinGame-GO/blob/main/mygo.gif?raw=true)

## 概要
初めの設定画面で試合のための情報を設定して「Play!」でゲーム画面に遷移できます。  
9x9, 13x13, 19x19で９路盤、１３路盤、１９路盤を選べます。  
碁盤上をクリックすることで確認の薄い〇が出てきて再度クリックすると石が打たれます。  
本来置けない交点でない場所の場合は打たれません。  
石をとったり地の計算は含まれていません。  
ただ盤面データは配列で保存されていてインターフェイスは用意されているのであとは簡単に各々のロジックを組めると思います。  
古い上少ししかコード量はありませんが誰かの参考になるときがあるかもしれないので公開します。  

## 開発環境（当時）
* Qt4
* C++
* ArchLinux

## コンパイル確認環境
* Qt6
* msvc2019

## ライセンス
本コードは[CC0](https://github.com/minfaox3/Painter/blob/main/LICENSE)のもと提供されます。