#setup django/mongodb dependencies
cd ~/del
virtualenv djangomongodbenv
cd djangomongodbenv
bash
source bin/activate
fish
pip install git+https://github.com/django-nonrel/django@nonrel-1.5
pip install git+https://github.com/django-nonrel/djangotoolbox
pip install git+https://github.com/django-nonrel/mongodb-engine
