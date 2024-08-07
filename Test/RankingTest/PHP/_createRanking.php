<?php
// データベースの作成と接続(既にある場合は接続のみ)
$db = new PDO('sqlite:ranking.db');

// ランキング用のテーブルを削除(無ければ無視)
$que = "DROP TABLE IF EXISTS Ranking";
$db->query($que);

// ランキング用のテーブルの作成(既にあれば無視)
$que = 'CREATE TABLE IF NOT EXISTS';
$que .= ' Ranking(rank integer primary key, clearTime integer)';
$db->query($que);

// テーブルのテストデータを初期化
$db->query("INSERT OR REPLACE INTO Ranking VALUES (1, 0)");
echo "INSERT OR REPLACE INTO Ranking VALUES (1, 0)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (2, 10)");
echo "INSERT OR REPLACE INTO Ranking VALUES (2, 10)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (3, 30)");
echo "INSERT OR REPLACE INTO Ranking VALUES (3, 30)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (4, 60)");
echo "INSERT OR REPLACE INTO Ranking VALUES (4, 60)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (5, 100)");
echo "INSERT OR REPLACE INTO Ranking VALUES (5, 100)"."<br>";

// テーブルのデータを確認
echo "【作成されたテーブルのデータ】"."<br>";
$que ="SELECT * From Ranking";
$value = $db->query($que);

// 連想配列として入ってるのでこれで出せる
foreach($value as $temp)
{
    echo $temp['rank'].",";
    echo $temp['clearTime']."<br>";
}
?>