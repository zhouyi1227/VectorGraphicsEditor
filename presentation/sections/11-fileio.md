---
layout: default
transition: slide-left
---

# 文件 I/O · .vgjson

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div class="dim" style="font-size:0.85rem;margin-bottom:1rem;">JSON 文本格式 · version 2 · 可读可编辑跨平台</div>

<div class="grid" style="display:grid;grid-template-columns:1fr 1fr;gap:1.5rem;">

<div style="overflow:hidden;">

```json
{
    "version": 2,
    "canvas": {
        "width": 1200,
        "height": 800
    },
    "shapes": [{
        "id": "a1b2…",
        "type": "rectangle",
        "rect": {
            "x": 100, "y": 100,
            "w": 200, "h": 150
        },
        "style": {
            "strokeEnabled": true,
            "strokeColor": "#000000",
            "strokeWidth": 2.0,
            "fillColor": "#80c8ff",
            "fillEnabled": true
        },
        "zValue": 1.0
    }]
}
```

</div>

<div>

<v-click>

<div style="border:1px solid #e8e8e8;border-radius:6px;padding:1rem;">

<div style="font-weight:600;font-size:0.85rem;margin-bottom:0.3rem;">FileManager — 静态工具类</div>

```cpp
class FileManager {
public:
    static void saveToFile(
        const DocumentData& doc,
        const QString& path);

    static std::optional<DocumentData>
    loadFromFile(
        const QString& path);
};
```

</div>

</v-click>

<v-click>

<div style="border:1px solid #e8e8e8;border-radius:6px;padding:1rem;margin-top:0.75rem;">

| 校验规则 | 行为 |
|----------|------|
| version ≠ 2 | 拒绝加载 |
| JSON 解析失败 | 返回 nullopt |
| 重复 shape ID | 拒绝加载 |
| 旋转变换矩阵 | 拒绝保存/加载 |
| 缺少字段 | 回退默认值 |

</div>

</v-click>

<v-click>

<div style="margin-top:0.75rem;padding:0.5rem 1rem;background:#fafafa;border:1px solid #eee;border-radius:4px;font-size:0.85rem;">

<strong>PNG 导出</strong> — QImage + QPainter 渲染 Scene → ARGB32 → image.save(path, "PNG")

</div>

</v-click>

</div>

</div>

<!--
文件格式选择JSON而非二进制：可读可编辑、跨平台无字节序问题、Qt有原生QJsonDocument支持、后续扩展字段无需改解析器结构。version字段为格式演化预留空间。FileManager设计为全静态方法，不维护任何状态。校验规则中不支持旋转变换矩阵，保存和加载时都会检测并拒绝，这是为了避免仿射变换带来的各种边界问题。PNG导出使用QImage + QPainter渲染方式，导出区域包含所有图形加上margin。
-->
