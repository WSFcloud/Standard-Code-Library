# Standard Code Library

算法竞赛模板库。

目前处于未完成状态。

部分代码来自网络。

## 本地编译 LaTeX

1. 安装 Python pygments 库：
```bsah
pip install pygments
```

2. 需要安装以下字体：
- Noto Serif CJK SC
- Noto Sans CJK SC

可以在[该仓库](https://github.com/notofonts/noto-cjk)下载并安装字体，或使用包管理器安装：
```bash
sudo apt install fonts-noto-cjk
```

3. 使用 xelatex 编译：
```bash
xelatex -shell-escape main.tex
```

## 自动构建
当 push 至远程仓库时，GitHub Action 会自动编译生成 PDF 文件并上传至 GitHub Release。