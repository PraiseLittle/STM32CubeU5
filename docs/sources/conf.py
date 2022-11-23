# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

import sys
import os

project = 'U5 devices'
copyright = '2022, STMicroelectronics'
author = 'STMicroelectronics'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions=['breathe', 'sphinx_rtd_theme','sphinx.ext.autodoc','myst_parser','sphinxcontrib.plantuml','sphinx.ext.graphviz', 'sphinxcontrib.images']


if sys.platform == "win32":
    plantuml = "java.exe -jar C:/Users/darochaj/Work/WorkDoc/STM32CubeU5/docs/sources/PlantUML/plantuml.jar"
else:
    plantuml = "plantuml" #TODO better ?

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


path_file = os.path.dirname(__file__)
print(f"This is the path file {path_file} and this is the working dir {os.getcwd()}")
breathe_projects = {"STM32Cube_U585": f"{path_file}/../_build/doxygen/U585/xml/", "STM32Cube_U575":f"{path_file}/../_build/doxygen/U575/xml/"}
breathe_domain_by_extension = {"h": "c"}

exclude_patterns = ['breathe/*']

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = "sphinx_rtd_theme"
html_static_path = ['../_static']
html_logo='../_static/ST_logo_2020_blue_no_tagline_rgb.svg'

set BUILDDIR=your/path/to/build