#include <cstdio>
#include <cstring>
int main(void)
{
    int n, nnz;
    int *rowptr;
    int *rows;
    int *cols;
    double *vals;
    char buf[100];
    FILE *fp = fopen("./matrix/MatrixA.00000", "r");
    int b1, b2, b3, b4;
    fscanf(fp, "%d%d%d%d\n", &b1, &b2, &b3, &n);
    n = n + 1;
    nnz = 0;

    // 获取元素个数
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        nnz++;
    }
    fclose(fp);
    rowptr = new int[n + 1];
    rows = new int[nnz];
    cols = new int[nnz];
    vals = new double[nnz];
    fp = fopen("./matrix/MatrixA.00000", "r");
    fscanf(fp, "%d%d%d%d\n", &b1, &b2, &b3, &b4);
    memset(rowptr, 0, sizeof(int) * (n + 1));
    // 正式读取
    for (int i = 0; i < nnz; i++)
    {
        fscanf(fp, "%d %d %lf", rows + i, cols + i, vals + i);
        rowptr[rows[i] + 1]++;
    }
    for (int i = 1; i < n + 1; i++)
    {
        rowptr[i] = rowptr[i - 1] + rowptr[i];
    }
    fclose(fp);
    printf("%d %d\n", n, nnz);

    for (int i = 0; i < n; i++)
    {
        // 遍历第i行
        for (int j = rowptr[i]; j < rowptr[i + 1]; j++)
        {
            int col = cols[j];
            // 如果到了上三角部分就退出第二层循环
            if (col >= i)
                break;
            else
            {
                // 查找a[j][i]，遍历a[j][:]
                for (int k = rowptr[col]; k < rowptr[col + 1]; k++)
                {
                    int col2 = cols[k];
                    if (col2 == i)
                    {
                        if (vals[k] == vals[j])
                            break;
                        else
                        {
                            // 存在a[j][i]，但值不相同
                            printf("bad value in (%d,%d):%lf    (%d,%d):%lf\n", i, col, vals[j], col, col2, vals[k]);
                            printf("matrix is unsym\n");
                            return 0;
                        }
                    }
                    else if (col2 > i)
                    {
                        // 不存在a[j][i]
                        printf("bad value in (%d,%d):%lf\n", i, col, vals[j]);
                        printf("matrix is unsym\n");
                        return 0;
                    }
                    else
                    {
                        // 不存在a[j][i], 这一行到最后了
                        if (k == rowptr[col + 1] - 1)
                        {
                            printf("bad value in (%d,%d):%lf\n", i, col, vals[j]);
                            printf("matrix is unsym\n");
                            return 0;
                        }
                    }
                }
            }
        }
    }
    printf("matrix is sym\n");

    // 释放
    delete[] rowptr;
    delete[] rows;
    delete[] cols;
    delete[] vals;
}
