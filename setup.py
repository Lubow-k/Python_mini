from setuptools import Extension, setup
setup(
    name="foreign",
    version="1.0.0",
    description="Python and C matrix",
    author="Lubov",
    author_email="vvv",
    ext_modules=[
        Extension(
            name="foreign",
            sources=["foreignmodule.c"],
        ),
    ]
)
