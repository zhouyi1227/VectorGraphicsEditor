---
layout: default
transition: slide-left
---

# 选中与变换

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div class="dim" style="font-size:0.85rem;margin-bottom:1rem;">MultiShapeSession 快照 · 按 Esc 撤销当前变换</div>

```mermaid {scale: 0.75}
%%{init: {'theme':'neutral'}}%%
sequenceDiagram
    participant U as 用户
    participant CV as CanvasView
    participant MS as MultiShapeSession
    participant SI as ShapeItem

    U->>CV: 鼠标按下（选中图形的手柄）
    CV->>MS: begin(items, frame)
    MS->>SI: 遍历选中项，读取 shapeData()
    MS-->>MS: 保存到 entries 列表

    loop 拖动
        U->>CV: 鼠标移动
        CV->>CV: scaledFrameFromHandle
        CV->>SI: 更新 transform
    end

    alt 释放 → 提交
        U->>CV: 鼠标释放
    else Esc → 取消
        U->>CV: 按 Esc
        CV->>MS: cancel()
        MS->>SI: 恢复所有快照
    end
```

<v-click>

<div style="margin-top:0.75rem;display:flex;gap:0.75rem;font-size:0.85rem;">

<div style="border:1px solid #e8e8e8;border-radius:4px;padding:0.5rem 1rem;flex:1;">
<strong>SelectionFrame</strong> — topLeft + xAxis + yAxis 表示任意朝向矩形
</div>

<div style="border:1px solid #e8e8e8;border-radius:4px;padding:0.5rem 1rem;flex:1;">
<strong>CanvasGeometry</strong> — 4 个缩放变换函数，Shift 保持比例
</div>

</div>

</v-click>

<!--
选中图形的变换操作通过MultiShapeSession实现快照机制，是简化版的备忘录模式。变换开始前保存所有选中图形的ShapeData快照，变换过程中实时更新transform。Esc取消时恢复所有快照数据。SelectionFrame用三个QPointF表示任意朝向矩形，可以处理旋转后的选中框。CanvasGeometry的scaledFrameFromHandle计算缩放变换矩阵，做了最小缩放限制0.01和Shift键保持比例的支持。
-->
