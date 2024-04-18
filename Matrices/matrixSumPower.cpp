
vector<vector<int>>unity, zero;


// In solve
    unity.resize(n, vector<int>(n));
    zero.resize(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(i == j)
                unity[i][j] = 1;
        }
    }

vector<vector<int>> addIdentity(vector<vector<int>> matrix)
{
    vector<vector<int>> ret = matrix;

    for (int i = 0; i < ret.size(); ++i) {
        for (int j = 0; j < ret[0].size(); ++j) {
            if(i == j)
            {
                ret[i][j] += 1;
            }
        }
    }

    return ret;
}

vector<vector<int>> matrix_multiply(vector<vector<int>> matrix1, vector<vector<int>> matrix2)
{
    int n1 = matrix1.size(), m1 = matrix1[0].size();
    int n2 = matrix2.size(), m2 = matrix2[0].size();
    vector<vector<int>>ans(n1, vector<int>(m2));
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m2; ++j) {
            for (int k = 0; k < n2; ++k) {
                ans[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return ans;
}

vector<vector<int>> matrix_power(vector<vector<int>> matrix, int n)
{
    if(n <= 0)
        return unity;

    vector<vector<int>> ret = matrix_power(matrix_multiply(matrix, matrix), n / 2);
    if(n&1)
        ret = matrix_multiply(ret, matrix);

    return ret;
}



vector<vector<int>> matrix_sum_power(vector<vector<int>> matrix, int n)
{
    if(n == 0)
        return zero;

    if(n&1)
        return matrix_multiply(matrix, addIdentity( matrix_sum_power(matrix, n - 1) ));

    return matrix_multiply(matrix_sum_power(matrix, n / 2), addIdentity( matrix_sum_power(matrix, n / 2) ));
}