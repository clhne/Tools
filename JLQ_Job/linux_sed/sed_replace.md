# sed 命令替换文本文件中的内容   
## 方法 ##
eg:    

	sed -i "s|/home/wujiyang/FaceProjects/|"/home/***/workspace/face_detection/MTCNN_TRAIN"|g" \
    prepare_data/assemble_pnet_imglist.py    

注：上面的命令将“prepare_data/assemble_pnet_imglist.py”中的所有“/home/wujiyang/FaceProjects/”都替换成了“/home/***/workspace/face_detection/MTCNN_TRAIN”    