// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.26912050;
  double density_weight = 0.27434226;
  double prefix_weight = 0.32554091;
  double neighborhood_weight = 0.34381963;
  double late_weight = 0.24513329;
  double critical_weight = 0.10861356;
  unsigned budget = 8;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
