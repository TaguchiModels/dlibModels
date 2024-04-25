# 日本人用にトレーニングした dlib の顔認証モデル  

![s-TaguchiModelsWithDlib](https://github.com/TaguchiModels/dlibModels/assets/167880914/9aaf0909-b092-42a8-99a4-56c138455bc4)

## ディープメトリックラーニングによる高品質の顔認証  
dlib には優秀な顔認証モデルがあります。しかし、残念ながら人種に偏りがあり、特に北東アジア人、とりわけ日本人に関してはまったく役に立たないと言っても過言ではありません。ですが、それは仕方のないことだと思います。訓練に使用した顔認証用のデータセットに偏りがあったためです。  

そこで私は日本人を中心とした多くのデータセットを収集し、ゼロから訓練を行いました。これには途方もない時間を要しましたが、ある程度は実用に耐えうる基準に達したと思います。日本人用に訓練したとは言っても欧米人の顔認証に関しても dlib のモデルに近い結果となってます。dlib のexample で用意されているハリウッドのアクション ヒーローの写真も dlib と同様に分類が可能です。  

冒頭の画像は日本人の俳優の分類を私のモデルで行ったモノです。  
この下の画像は dlib『dlib_face_recognition_resnet_model_v1.dat』モデルを使用したときの分類結果です。  

![dlib_japannese_bald_actor](https://github.com/TaguchiModels/dlibModels/assets/167880914/29b2776c-8e9b-47e9-aeec-778f4ba8009e)

# LFWデターセットによる dlib との精度の比較
私はある程度の客観性を提示するために LFW デターセットによる精度をテストしました。  
まずは dlib のモデル "dlib_face_recognition_resnet_model_v1.dat" でテストしました。  
結果は 0.993833% でした。

```
dlib original verasin
C:\Users\Taguchi\Desktop\dlib_face_recognition_resnet_model_v1_lfw_test\build>main
dist thresh: 0.6
margin: 0.04
overall lfw accuracy: 0.993833
pos lfw accuracy: 0.994667
neg lfw accuracy: 0.993
fold mean: 0.995
fold mean: 0.991667
fold mean: 0.991667
fold mean: 0.99
fold mean: 0.996667
fold mean: 0.996667
fold mean: 0.99
fold mean: 0.995
fold mean: 0.996667
fold mean: 0.995
rscv.mean(): 0.993833
rscv.stddev(): 0.00272732
ERR accuracy: 0.993
ERR thresh: 0.595778
```

続いて私のモデル "taguchi_face_recognition_resnet_model_v1.dat" でテストしました。  
結果は 0.9895% でした。

```
Taguchi model version
C:\Users\Taguchi\dlib_face_recognition_resnet_model_v1_lfw_test\build>main
dist thresh: 0.6
margin: 0.04
overall lfw accuracy: 0.9895
pos lfw accuracy: 0.984
neg lfw accuracy: 0.995
fold mean: 0.986667
fold mean: 0.99
fold mean: 0.986667
fold mean: 0.99
fold mean: 0.988333
fold mean: 0.993333
fold mean: 0.981667
fold mean: 0.993333
fold mean: 0.991667
fold mean: 0.993333
rscv.mean(): 0.9895
rscv.stddev(): 0.00377205
ERR accuracy: 0.989
ERR thresh: 0.614296
```

ご覧のように dlib と私のモデルでは 0.004333% dlib のほうが精度を上回っています。  
この精度の差は誤差の範囲と言えるでしょう。  
実際、北東アジア人の顔認証を無料で手に入れたいと考える人にとっては朗報です。  

LFWデータセットはここから入手しました。
[LFW dataset](http://vis-www.cs.umass.edu/lfw/)

# 650万の顔データセットによる訓練
私の顔認証モデルの訓練には、16000人以上の人物の顔を合計で650万枚以上使用しました。  
このうち約47%が日本人(日本人以外のアジア人も若干含む)の顔データです。  
この訓練用データセットはいくつかの公開されていたデータセットに加えて、インターネットから収集したものを加えました。  
最も苦労したのは、いくつかのデータセットの中には重複した人物が含まれていることです。  
この重複した人物を取り除くことに多くの時間を要しました。  

# 顔認証モデルの入手
dlib のモデル 'dlib_face_recognition_resnet_model_v1.dat' は以下のリンクより取得してください。  

[dlib.net/files](http://dlib.net/files/)

私のモデル 'taguchi_face_recognition_resnet_model_v1.dat' は、まもなく掲載する予定です。  
2024年5月のGW明けまでに準備が完了する見込みです。  
今しばらくお待ちください。

# コンパイル方法
dlib.net にコンパイル方法が記載されていますので参考にしてください。  
[How to compile dlib](http://dlib.net/compile.html)

# 制限事項
私のモデルには訓練用データが不足しているため、精度が著しく悪い場合があります。  
*18未満の人物  
*アフリカ系の人物  
上記の用途には向かないことがあります。  
注意してご利用ください。  


`このREAD.meは執筆途中です`
