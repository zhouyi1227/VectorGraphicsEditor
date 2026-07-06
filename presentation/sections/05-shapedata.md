---
layout: default
transition: slide-left
---

# 功能总览

<style>
.deck-lead { margin-bottom: 0.5rem; font-size: 0.88rem; line-height: 1.4; }
.process-row { gap: 0.45rem; }
.process-row.mb-6 { margin-bottom: 0.6rem !important; }
.process-step { padding-top: 0.4rem; }
.process-title { font-size: 0.86rem; }
.process-copy { font-size: 0.72rem; line-height: 1.35; }
.rail-copy { font-size: 0.78rem; line-height: 1.4; }
.rail-title { font-size: 0.88rem; }
.deck-stage { padding: 0.65rem 0.9rem; }
.rail-list { gap: 0.4rem; }
.rail-item { padding-left: 0.7rem; }
.split-even { gap: 0.8rem; }
.eyebrow { font-size: 0.7rem; }
</style>

<div class="deck-rule"></div>

<div class="deck-lead">
  从用户视角看，系统能力可以拆成五步：选工具、在画布中创建图形、修改属性与几何、批量变换、文档保存。这五步走完，编辑链路就闭合了。
</div>

<div class="process-row mb-6">
  <div v-click class="process-step">
    <div class="process-no">STEP 01</div>
    <div class="process-title">选工具</div>
    <div class="process-copy">点、线、折线、多边形、圆、椭圆、矩形。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">STEP 02</div>
    <div class="process-title">创建图形</div>
    <div class="process-copy">单击、拖拽、逐点累加，过程实时显示 preview。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">STEP 03</div>
    <div class="process-title">改属性</div>
    <div class="process-copy">改描边、线型、填充与几何参数。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">STEP 04</div>
    <div class="process-title">多选 + 变换</div>
    <div class="process-copy">框选、平移、四角缩放，Shift 保持比例。</div>
  </div>
  <div v-click class="process-step">
    <div class="process-no">STEP 05</div>
    <div class="process-title">保存 + 导出</div>
    <div class="process-copy"><code>.vgjson</code> 持久化，PNG 导出。</div>
  </div>
</div>

<div class="split-even">
  <div class="deck-stage">
    <div class="eyebrow">创建链路</div>
    <div class="thin-divider"></div>
    <div class="rail-list">
      <div v-click class="rail-item">
        <div class="rail-title"><code>Point</code></div>
        <div class="rail-copy">单击即生成，离散图元。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>Line / Circle / Ellipse / Rectangle</code></div>
        <div class="rail-copy">按下、拖拽、释放，由对角线或包围框定义几何。</div>
      </div>
      <div v-click class="rail-item">
        <div class="rail-title"><code>Polyline / Polygon</code></div>
        <div class="rail-copy">逐点累加，<code>Enter</code> 或双击结束。</div>
      </div>
    </div>
  </div>
  <div class="rail-list">
    <div v-click class="rail-item">
      <div class="rail-index">编辑</div>
      <div class="rail-title">实时反馈</div>
      <div class="rail-copy">属性面板与选中状态联动，复制、粘贴、删除、拖拽即时可见。</div>
    </div>
    <div v-click class="rail-item">
      <div class="rail-index">桌面体验</div>
      <div class="rail-title">中英文 + 主题</div>
      <div class="rail-copy">语言和外观可切换，重启后保留。</div>
    </div>
  </div>
</div>

<!--
各位老师，这一页我先把系统的能力清单说清楚。五步是：选工具、创建、改属性、多选变换、保存导出。重点是创建链路分两条：拖拽创建适合 Line、Circle、Ellipse、Rectangle 这种有包围盒的图形，路径创建适合 Polyline、Polygon 这种需要逐点采样的图形。这两条链路在后面讲策略模式那一页会对应到 DragCreationStrategy 和 PathCreationStrategy，是同一组鼠标事件流分到两个策略里完成的。编辑链路里属性面板和选中状态联动，复制粘贴有 16 像素的偏移避免和原图重叠。下面我进入四层架构。
-->
