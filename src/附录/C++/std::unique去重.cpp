sort(a.begin(), a.end()); // 要求必须有序
a.erase(unique(a.begin(), a.end()), a.end());