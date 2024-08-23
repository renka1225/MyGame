<?php
// データベースの作成と接続(既にある場合は接続のみ)
$db = new PDO('sqlite:ranking.db');

// ランキング用のテーブルを削除(なければ無視)
$que = "DROP TABLE IF EXISTS Ranking";
$db->query($que);

// ランキング用のテーブルの作成(既にあれば無視)
$que = 'CREATE TABLE IF NOT EXISTS';
$que .= ' Ranking(rank integer primary key, clearTime integer)';
$db->query($que);

// テーブルのテストデータを初期化
$db->query("INSERT OR REPLACE INTO Ranking VALUES (1,5000)");
echo "INSERT OR REPLACE INTO Ranking VALUES (1, 5000)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (2,6000)");
echo "INSERT OR REPLACE INTO Ranking VALUES (2, 6000)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (3,7000)");
echo "INSERT OR REPLACE INTO Ranking VALUES (3, 7000)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (4, 8000)");
echo "INSERT OR REPLACE INTO Ranking VALUES (4, 8000)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (5, 9000)");
echo "INSERT OR REPLACE INTO Ranking VALUES (5, 9000)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (6, 10000)");
echo "INSERT OR REPLACE INTO Ranking VALUES (6, 10000)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (7, 11000)");
echo "INSERT OR REPLACE INTO Ranking VALUES (7, 11000)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (8, 12000)");
echo "INSERT OR REPLACE INTO Ranking VALUES (8, 12000)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (9, 13000)");
echo "INSERT OR REPLACE INTO Ranking VALUES (9, 13000)"."<br>";
$db->query("INSERT OR REPLACE INTO Ranking VALUES (10, 14000");
echo "INSERT OR REPLACE INTO Ranking VALUES (10, 14000)"."<br>";

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