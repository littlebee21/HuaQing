# !bin/bash/

git init

#git clone git@github.com:littlebee21/HuaQing.git

#add file to push
git checkout -b


# 添加对应的内容 然后进行递交
echo "hello" >> README.md
git add README.md
git add .
git commit -m "first commit"

#set branch and respos
git branch -M main

# 设置远程仓库，ssh方式的不需要使用密码
# git remote add origin https://github.com/littlebee21/siwei.git
git remote add origin git@github.com:littlebee21/HuaQing.git


#orgin 是起源的意思 main是分治
git push -u origin main
#git push -u -f orgin main
