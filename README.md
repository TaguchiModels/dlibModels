# 日本人用にトレーニングした dlib の顔認証モデル  

![s-TaguchiModelsWithDlib](https://github.com/TaguchiModels/dlibModels/assets/167880914/9aaf0909-b092-42a8-99a4-56c138455bc4)

## ディープメトリックラーニングによる高品質の顔認証  
dlib には優秀な顔認証モデルがあります。しかし、残念ながら人種に偏りがあり、特に北東アジア人、とりわけ日本人に関してはまったく役に立たないと言っても過言ではありません。ですが、それは仕方のないことだと思います。訓練に使用した顔認証用のデータセットに偏りがあったためです。  

そこで私は日本人を中心とした多くのデータセットを収集し、ゼロから訓練を行いました。これには途方もない時間を要しましたが、ある程度は実用に耐えうる基準に達したと思います。日本人用に訓練したとは言っても欧米人の顔認証に関しても dlib のモデルに近い結果となってます。dlib の example で用意されているハリウッドのアクション ヒーローの写真も dlib と同様に分類が可能です。  

冒頭の画像は日本人の俳優の分類を私のモデルで行ったモノです。  
この下の画像は dlib『dlib_face_recognition_resnet_model_v1.dat』モデルを使用したときの分類結果です。  

![dlib_japannese_bald_actor](https://github.com/TaguchiModels/dlibModels/assets/167880914/29b2776c-8e9b-47e9-aeec-778f4ba8009e)

## LFWデターセットによる dlib との精度の比較
私はある程度の客観性を提示するために LFW デターセットによる精度をテストしました。  
まずは dlib のモデル "dlib_face_recognition_resnet_model_v1.dat" でテストしました。  
結果は 0.993833% でした。

```
dlib original version
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

## 650万枚の顔データセットによる訓練
私の顔認証モデルの訓練には、16,000人以上の人物の顔を合計で650万枚以上使用しました。  
このうち約47%が日本人(日本人以外のアジア人も若干含む)の顔データです。  
この訓練用データセットはいくつかの公開されていたデータセットに加えて、インターネットから収集したものを加えました。  
最も苦労したのは、いくつかのデータセットの中には重複した人物が含まれていることです。  
この重複した人物を取り除くことに多くの時間を要しました。  

## 顔認証モデルの入手
dlib のモデル 'dlib_face_recognition_resnet_model_v1.dat' および 'shape_predictor_5_face_landmarks.dat'は以下のリンクより取得してください。  
 `※ 拡張子に'.bz2'が付いていますので、ダウンロード後に解凍してください`  

[dlib.net/files](http://dlib.net/files/)

## コンパイル方法
dlib.net にコンパイル方法が記載されていますので参考にしてください。  
[How to compile dlib](http://dlib.net/compile.html)

## 実行  
コンパイル後に出来たexeファイルと同じフォルダーに以下を配置してください。  
 * faces フォルダーを配置して、その配下に JapaneseBaldActor.jpg, bald_guys.jpg を配置してください。  
 * 'dlib_face_recognition_resnet_model_v1.dat' を配置してください。  
 * 'shape_predictor_5_face_landmarks.dat' を配置してください。  
 * 'taguchi_face_recognition_resnet_model_v1.dat' を配置してください。  

コマンドプロンプトより以下のコマンドを打ってください。  
 * Taguchi model の例  
    ```
    > dnn_face_recognition_ex faces/JapaneseBaldActor.jpg taguchi_face_recognition_resnet_model_v1.dat
    ```  
 * dlib model の例
    ```
    > dnn_face_recognition_ex faces/JapaneseBaldActor.jpg dlib_face_recognition_resnet_model_v1.dat  
    ```
    
## 制限事項
私のモデルには訓練用データが不足しているため、精度が著しく悪い場合があります。  
 * アフリカ系のルーツを持つ人物  
 * 18歳未満の人物  
 * マスクを付けている人物  

上記の用途には向かないことがあります。  
注意してご利用ください。  

---

# 日本人用にトレーニングした dlib の 性別判定モデル  

![Gender_males](https://github.com/TaguchiModels/dlibModels/assets/167880914/9db5205e-e5c9-4828-b4fd-5591d874a3c2)

## dlib の性別判定モデルも日本人を誤判定  
dlib には優秀な性別判定モデルがあります。しかし、残念ながらこれも人種に偏りがあり、特に北東アジア人、とりわけ日本人に関してはまったく役に立たないと言っても過言ではありません。理由は先ほどと同様に訓練に使用した顔認証用のデータセットに偏りがあったためです。  

そこで私は日本人を中心とした多くのデータセットを収集し、これもゼロから訓練を行いました。日本人用に訓練したとは言っても欧米人の性別判定に関しても dlib のモデルに遜色ない結果となってます。とはいえ dlib の 性別判定モデル "dnn_gender_classifier_v1.dat" は非常に軽いモデルです。私のモデルはdlib の "resnet34_1000_imagenet_classifier.dnn" を男女の性別判定にソースコードを変更して訓練したものであり、重たいモデルとなっています。  
もっとも重たいのはモデルを読み込み desesialize する冒頭部分であり、性別判定処理にかかる時間はそれほどでもありません。  
それでも、あなたの利用範囲が欧米人に特化している場合は dlib のモデルを使用した方が良いでしょう。  

dlib の性別判定モデルのソースコードは、github/dlib 'dnn_gender_classifier_v1_ex.cpp' を参照し、使い方はそちらを直接ご覧ください。  
[github dlib](https://github.com/davisking/dlib/examples)

## 50万枚の顔データセットによる訓練  
私の性別判定モデルの訓練には、顔画像ファイルを合計で50万枚以上使用しました。  
このうち約40%が日本人(日本人以外のアジア人も若干含む)の顔データです。  
この訓練用データセットはいくつかの公開されていたデータセットに加えて、インターネットから収集したものを加えました。  

## コンパイル方法
私の性別判定モデルのソースコードは、'GenderModelClassifier.cpp' です。  
dlib.net にコンパイル方法が記載されていますので参考にしてください。  
[How to compile dlib](http://dlib.net/compile.html)

## Taguchi モデルの実行  
コンパイル後に出来たexeファイルと同じフォルダーに以下を配置してください。  
 * gender フォルダーとその中にある日本人の若手俳優の顔画像ファイルを配置してください。  
 * 'shape_predictor_5_face_landmarks.dat' を配置してください。  
 * 'taguchi_model_gender_classifier.dnn' を配置してください。  

コマンドプロンプトより以下のコマンドを打ってください。  
 * Taguchi model の例  
    ```
    > GenderModelClassifier gender
    ```  

実行すると下記のように精度とともに 'male' 'female' で判定結果が表示されます。  

![GenderModelResult](https://github.com/TaguchiModels/dlibModels/assets/167880914/d09e81a1-d32a-43cc-a9d7-b004e121e618)
    
## 制限事項
私のモデルには訓練用データが不足しているため、精度が著しく悪い場合があります。  
 * アフリカ系のルーツを持つ人物  
 * 18歳未満の人物  
 * マスクを付けている人物  

上記の用途には向かないことがあります。  
注意してご利用ください。  
