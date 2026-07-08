---
layout: default
transition: slide-left
---

# 关键设计取舍 / 难点解决

<div class="deck-rule"></div>

<div class="statement-band mb-5">
  三个主动取舍，每条都有具体的失败场景作为出发点。
</div>

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">取舍 1</div>
    <div class="rail-title">数据与视图分离</div>
    <div class="rail-copy"><code>CanvasView</code> 不直接读写 <code>ShapeItem</code> 内部状态，通过 <code>ShapeData</code> 与工厂 / setter 交互。序列化和复制逻辑因此保持稳定。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">取舍 2</div>
    <div class="rail-title">属性面板防重入</div>
    <div class="rail-copy"><code>m_updatingWidgets</code> 标志位阻断「程序更新控件 → valueChanged → 再次 emit」死循环，界面稳定性的关键保护。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">取舍 3</div>
    <div class="rail-title">几何与文件契约保守收敛</div>
    <div class="rail-copy">缩放抽成 <code>SelectionFrame + CanvasGeometry</code>，文件固定 <code>version 2</code> 并拒绝旋转 transform，避免交互与 I/O 语义同时失控。</div>
  </div>
</div>

<!--
各位老师，三个主动取舍，每条对应具体失败场景。第一条早期尝试直接读写 ShapeItem 内部字段，每次改状态都要改一堆。第二条属性面板不阻断就是死循环。第三条几何和文件格式锁定避免语义失控。
-->
