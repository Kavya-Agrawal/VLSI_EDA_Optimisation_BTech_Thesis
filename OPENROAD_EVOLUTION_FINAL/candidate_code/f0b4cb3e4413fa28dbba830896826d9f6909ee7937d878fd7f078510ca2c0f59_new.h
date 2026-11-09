// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.47157861;
  double density_weight = 0.25371475;
  double prefix_weight = 0.48440128;
  double neighborhood_weight = 0.08522871;
  double late_weight = 0.16330027;
  double critical_weight = 0.29420618;
  unsigned budget = 24;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
