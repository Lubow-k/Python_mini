#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>



void nullCheck(void* ptr) {
    if (ptr == NULL) {
        printf("Out of memory");
        exit(0);
    }
}

void madeArr(size_t len, float*** retarr) {
    float** arr = (float**)malloc(len * sizeof(float*));
    nullCheck(arr);
    for (size_t i = 0; i < len; i++) {
        arr[i] = (float*)malloc(len * sizeof(float));
        nullCheck(arr[i]);
    }
    *retarr = arr;
}

float** Power_matrix(float** matrix, int p, int len) {
    float** result_matrix = NULL;
    madeArr(len, &result_matrix);
    float** new_matrix = NULL;
    madeArr(len, &new_matrix);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (i == j)
                new_matrix[i][j] = 1;
            else new_matrix[i][j] = 0;
        }
    }

    for (int k = 0; k < p; k++) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                result_matrix[i][j] = 0;
                for (int r = 0; r < 2; r++) {
                    result_matrix[i][j] += (new_matrix[i][r] * matrix[r][j]);
                }
            }
        }

        for (int e = 0; e < 2; e++){
            for (int w = 0; w < 2; w++)
            {
                new_matrix[e][w] = result_matrix[e][w];
            }
        }
    }
    return result_matrix;
}

static PyObject *matrix_power(PyObject* self, PyObject* args) {
    PyObject* obj_list;
    int power;
    if (!PyArg_ParseTuple(args, "Oi", &obj_list, &power)) {
        return NULL;
    }

    int len = PyObject_Length(obj_list);
    float** matrix = NULL;
    madeArr(len, &matrix);

    for (int i = 0; i < len; i++) {
        PyObject* item = PyList_GetItem(obj_list, i);
        for (int t = 0; t < len; t++) {
            matrix[i][t] = PyFloat_AsDouble(PyList_GetItem(item, t));
        }
    }
    matrix = Power_matrix(matrix, power, len);
    
    for (int i = 0; i < len; i++) {
        PyObject* item = PyList_GetItem(obj_list, i);
        for (int t = 0; t < len; t++) {
            PyList_SetItem(item, t, PyFloat_FromDouble(matrix[i][t]));
        }
    }

    return obj_list;
}


static PyMethodDef ForeignMethods[] = {
    {"matrix_power", matrix_power, METH_VARARGS,
    "Matrix_power"
    },
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef foreignmodule = {
    PyModuleDef_HEAD_INIT,
    "foreign", /* name of module */
    NULL, /* module documentation, may be NULL */
    -1, /* size of per-interpreter state of the module,
        or -1 if the module keeps state in global variables. */
    ForeignMethods
};

PyMODINIT_FUNC PyInit_foreign(void) {
    return PyModule_Create(&foreignmodule);
}
