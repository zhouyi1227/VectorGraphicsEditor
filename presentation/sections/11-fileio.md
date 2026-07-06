---
layout: default
transition: slide-left
---

# 事件分发流程

<div class="deck-rule"></div>

<div class="deck-lead">
  事件页的核心问题不是“有哪些回调函数”，而是“同一时刻哪个会话拥有控制权”。
  输入一旦进入某个会话，后续事件就不会再误流向别的路径。
</div>

<div class="deck-stage diagram-frame">

```mermaid
flowchart TD
  A["mousePressEvent"] --> B{"Select + 命中手柄?"}
  B -- yes --> C["beginTransformSession"]
  B -- no --> D{"当前工具"}
  D -- Point --> E["直接 addShape"]
  D -- DragTool --> F["m_dragStrategy->begin"]
  D -- PathTool --> G["activePathStrategy()->begin"]

  H["mouseMoveEvent"] --> I{"已有会话?"}
  I -- 变换 --> J["updateTransformSession"]
  I -- 平移 --> K["updateSelectionDrag"]
  I -- 创建 --> L["strategy->update"]

  M["mouseReleaseEvent"] --> N["finishTransform / finishDrag / finishSelectionDrag"]
  O["keyPressEvent"] --> P["Enter 完成路径 / Esc 取消 / Delete 删除 / Ctrl+C/V 复制粘贴"]
```

  <div class="diagram-caption">事件从鼠标与键盘入口进入，但真正的几何计算和图形创建在更下游的组件中完成。</div>
</div>

<div class="split-even mt-5">
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">ROUTE</div>
      <div class="rail-title">先分发，再计算</div>
      <div class="rail-copy"><code>CanvasViewInput.cpp</code> 负责识别当前模式并决定事件流向，几何计算被下放到策略和 <code>CanvasGeometry</code>。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">PRIORITY</div>
      <div class="rail-title">手柄优先级高于普通选中</div>
      <div class="rail-copy">这样用户拖缩放柄时不会误触发 item selection，缩放与平移的意图边界更清楚。</div>
    </div>
  </div>
  <div class="deck-stage tight">
    <v-switch>
      <template #1>
        <div class="statement-band">鼠标按下时先判断“是不是在缩放”，再决定是否进入创建或拖拽。</div>
      </template>
      <template #2>
        <div class="statement-band">鼠标移动时只服务当前活动会话，避免状态交叉污染。</div>
      </template>
      <template #3>
        <div class="statement-band">键盘事件负责结束、取消和编辑命令，补全整套交互闭环。</div>
      </template>
    </v-switch>
  </div>
</div>

<!--
这一页讲“输入状态机”。最重要的点是：不同会话互斥，事件只会流向一个明确入口。比如变换会话开始后，mouseMove 不再进入普通拖拽创建逻辑，这样状态才稳定。
-->
