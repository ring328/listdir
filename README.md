# listdir for my Rickey

If you want to ls for millions of files in a directory, this is for you.


## usage

### listdir

Simply list files in `dirname` with prefix, space, and file path.

- prefix
  - f: regular file
  - d: directory
  
```bash:
$ ./listdir dirname
```

### listdir-fs

List files in `dirname` with prefix, space, filesize, space, and file path.
  
```bash:
$ ./listdir-fs dirname
```


## examples

```bash:
$ ./listdir /share/dataset/HVU/video360p | head
f /share/dataset/HVU/video360p/c9mUVAhyGhI_000012_000022_.mp4
f /share/dataset/HVU/video360p/4jbc7XTOU2o_000152_000162_.mp4
f /share/dataset/HVU/video360p/xg9uakufw7g_000251_000261_.mp4
f /share/dataset/HVU/video360p/OCbrOOk2tC4_000185_000195_.mp4
f /share/dataset/HVU/video360p/vPESNG_6GsA_000001_000011_.mp4
f /share/dataset/HVU/video360p/kfdV4hgq-DM_000248_000258_.mp4
f /share/dataset/HVU/video360p/hXnuYhzIzHQ_000001_000011_.mp4
f /share/dataset/HVU/video360p/swXZd37K4zU_000023_000033_.mp4
f /share/dataset/HVU/video360p/EMo6xiY1eDE_000000_000010_.mp4
f /share/dataset/HVU/video360p/32XVL8YBX9c_000075_000085_.mp4
$ time ./listdir /share/dataset/HVU/video360p | wc
   440087    880174  27285342

real    0m0.153s
user    0m0.177s
sys     0m0.057s
```


```bash:
$ ./listdir-fs /share/dataset/HVU/video360p | head
f 1812994 /share/dataset/HVU/video360p/c9mUVAhyGhI_000012_000022_.mp4
f 1020219 /share/dataset/HVU/video360p/4jbc7XTOU2o_000152_000162_.mp4
f 660840 /share/dataset/HVU/video360p/xg9uakufw7g_000251_000261_.mp4
f 1320733 /share/dataset/HVU/video360p/OCbrOOk2tC4_000185_000195_.mp4
f 598587 /share/dataset/HVU/video360p/vPESNG_6GsA_000001_000011_.mp4
f 678586 /share/dataset/HVU/video360p/kfdV4hgq-DM_000248_000258_.mp4
f 198942 /share/dataset/HVU/video360p/hXnuYhzIzHQ_000001_000011_.mp4
f 1599865 /share/dataset/HVU/video360p/swXZd37K4zU_000023_000033_.mp4
f 367062 /share/dataset/HVU/video360p/EMo6xiY1eDE_000000_000010_.mp4
f 567369 /share/dataset/HVU/video360p/32XVL8YBX9c_000075_000085_.mp4
$ time ./listdir-fs /share/dataset/HVU/video360p | wc
   440087   1320261  30429514

real    0m0.583s
user    0m0.260s
sys     0m0.455s
```


## References

- [You can list a directory containing 8 million files! But not with ls.](http://be-n.com/spw/you-can-list-a-million-files-in-a-directory-but-not-with-ls.html)
  - [getdents(2) — Linux manual page](https://man7.org/linux/man-pages/man2/getdents.2.html)
- [ファイル数が多すぎるフォルダで「ls」コマンドが遅くなってしまう問題の解決方法](https://gigazine.net/news/20210818-million-files-long-time-ls/)

