<?php
// データベースの作成と接続(既にある場合は接続のみ)
$db = new PDO('sqlite:ranking.db');

// データの受け取り
$getClearTime = $_GET['clearTime'];

// 新しいクリア時間をデータベースに挿入
$que = "INSERT INTO Ranking (clearTime) VALUES ('{$getClearTime}')";
$db->query($que);

// データを昇順にソートする
$que ="SELECT * FROM Ranking ORDER BY clearTime";
//連想配列にする
$value = $db->query($que)->fetchAll();

// 受け取ったデータを配列に挿入
$arr = [];
$arr[$getClearTime] = $getClearTime;

// テーブルデータの書き直し
$rank=1;
foreach($arr as $key => $temp)
{
    $que ="INSERT OR REPLACE INTO Ranking VALUES ({$rank},'{$key}')";
    echo $que."\n";
    $rank++;
}
?>