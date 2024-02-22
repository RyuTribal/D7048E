from django.urls import path
from .views import BasicAPI

urlpatterns = [
    path('model/', BasicAPI.as_view(), name='post_api'),
]