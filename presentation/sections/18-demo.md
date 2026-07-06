---
layout: default
transition: slide-left
---

# 关键设计取舍 / 难点解决

<div class="deck-rule"></div>

<div class="statement-band mb-6">
  我在这个项目里优先选择“可解释、可测试、可维护”的解，而不是短期内最省代码的解。
</div>

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">CHOICE 01</div>
    <div class="rail-title">数据与视图分离</div>
    <div class="rail-copy"><code>CanvasView</code> 不直接读写 <code>ShapeItem</code> 内部状态，而是通过 <code>ShapeData</code> 与工厂 / setter 交互，让序列化和复制逻辑保持稳定。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">CHOICE 02</div>
    <div class="rail-title">属性面板防重入</div>
    <div class="rail-copy"><code>m_updatingWidgets</code> 专门阻断“程序更新控件 → valueChanged → 再次 emit”的死循环，这是界面稳定性的关键保护层。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">CHOICE 03</div>
    <div class="rail-title">几何与文件契约保守收敛</div>
    <div class="rail-copy">缩放抽象成 <code>SelectionFrame + CanvasGeometry</code>，文件格式固定为 <code>version 2</code> 并拒绝旋转 transform，避免交互与 I/O 语义同时失控。</div>
  </div>
</div>

<!--
这页适合回答“你觉得自己项目里最有价值的设计是什么”。可以把它理解成答辩里的方法论总结：哪些地方是主动设计出来的，而不是功能自然堆出来的。
-->
