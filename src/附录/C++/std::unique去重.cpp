sort(a.begin(), a.end()); // 要求必须有序
a.erase(a.begin(), unique(a.begin(), a.end()));